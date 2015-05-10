/* Smarter assert replacement for LHS/RHS values. zlib/libpng licensed.
 * - rlyeh ~~ listening to Tuber / Desert Overcrowded
 */

/* Private API */

#ifndef ASSUME_HPP_HEADER
#define ASSUME_HPP_HEADER

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <deque>
#include <string>
#include <sstream>

namespace assume {
    class check {
        bool ok;
        std::deque< std::string > xpr;
        template<typename T> static std::string to_str( const T &t ) { std::stringstream ss; return (ss << t) ? ss.str() : "??"; }
    public:
        check( const char *const text, const char *const file, int line, bool result )
        :   xpr(4), ok(result)
        { xpr[0] = std::string(file) + ':' + to_str(line); xpr[2] = text; }

        ~check() {
            if( xpr.empty() ) return;
            operator bool();
            xpr[0] = xpr[0] + xpr[1];
            xpr.erase( xpr.begin() + 1 );
            if( !ok ) {
                xpr[2] = xpr[2].substr( xpr[2][2] == ' ' ? 3 : 4 );
                xpr[1].resize( (xpr[1] != xpr[2]) * xpr[1].size() );
                std::string buf;
                buf = "<assume.hpp> says: expression failed! (" + xpr[1] + ") -> (" + xpr[2] + ") -> (unexpected) at " + xpr[0] + "\n";
                fprintf(stderr, "%s", buf.c_str() );
                // assert fallback here
                fclose( stderr );
                fclose( stdout );
                assert( !"<assume.hpp> says: expression failed!" );
                // user defined fallbacks here
                for(;;) {}
            };
        }
#       define assume$impl(OP) \
        template<typename T> check &operator OP( const T &rhs         ) { return xpr[3] += " "#OP" " + to_str(rhs), *this; } \
        template<unsigned N> check &operator OP( const char (&rhs)[N] ) { return xpr[3] += " "#OP" " + to_str(rhs), *this; }
        operator bool() {
            if( xpr.size() >= 3 && xpr[3].size() >= 6 ) {
                char sign = xpr[3].at(xpr[3].size()/2+1);
                bool equal = xpr[3].substr( 4 + xpr[3].size()/2 ) == xpr[3].substr( 3, xpr[3].size()/2 - 3 );
                ok = ( sign == '=' ? equal : ( sign == '!' ? !equal : ok ) );
            } return ok;
        }
        assume$impl( <); assume$impl(<=); assume$impl( >); assume$impl(>=); assume$impl(!=); assume$impl(==); assume$impl(^=);
        assume$impl(&&); assume$impl(&=); assume$impl(& ); assume$impl(||); assume$impl(|=); assume$impl(| ); assume$impl(^ );
#       undef assume$impl
    };
}

#endif

/* Public API */

#include <cassert>

#ifdef assume
#undef assume
#endif

#if !(defined(NDEBUG) || defined(_NDEBUG))
#define assume(...) ( bool(__VA_ARGS__) ? \
        ( assume::check(#__VA_ARGS__,__FILE__,__LINE__,1) < __VA_ARGS__ ) : \
        ( assume::check(#__VA_ARGS__,__FILE__,__LINE__,0) < __VA_ARGS__ ) )
#else
#define assume assert
#endif
