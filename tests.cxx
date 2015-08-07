#include "assume.hpp"
#include "assume.hpp" // check header can be included twice

void cmp( int x ) {
    assume( x );
    assume( 0 == !x );
    assume( !x == 0 );
    assume( !!x );
    assume( !!x );
}
void cmpL( int x, int y ) {
    cmp(x);
    cmp(y);
    assume( x < y );
    assume( y > x );
    assume( x <= y );
    assume( y >= x );
    assume( x != y );
    assume( y != x );

    assume( !(x > y) );
    assume( !(y < x) );
    assume( !(x >= y) );
    assume( !(y <= x) );
    assume( !(x == y) );
    assume( !(y == x) );
}
void cmpG( int x, int y ) {
    cmp(x);
    cmp(y);
    assume( x > y );
    assume( y < x );
    assume( x >= y );
    assume( y <= x );
    assume( x != y );
    assume( y != x );

    assume( !(x < y) );
    assume( !(y > x) );
    assume( !(x <= y) );
    assume( !(y >= x) );
    assume( !(x == y) );
    assume( !(y == x) );
}
void cmpE( int x, int y ) {
    cmp(x);
    cmp(y);
    assume( x == y );
    assume( y == x );

    assume( !(x != y) );
    assume( !(y != x) );
}

int main() {
    int a = 1, b = 2;
    assume( a < b );
    assume( b > a );
    assume( a <= b );
    assume( b >= a );
    assume( a != b );
    assume( b != a );

    int z = 0, o = 1, t = 2;
    assume(o);
    assume(o+o);
    assume(!z);
    assume( o == o );
    assume( z != o );
    assume( o < t );
    assume( o <= t );
    assume( t > o );
    assume( t >= o );

    cmpL(8335,10002);
    cmpG(10002,8335);
    cmpE(8335,8335);
}
