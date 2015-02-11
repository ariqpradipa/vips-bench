// compile with
// g++ vips8.cc `pkg-config vips-cpp --cflags --libs`

#include <vips/vips8>

using namespace vips;

int 
main( int argc, char **argv )
{
	GOptionContext *context;
	VipsImage *global;

	GError *error = NULL;

	if( VIPS_INIT( argv[0] ) )
		return( -1 );

	context = g_option_context_new( " - VIPS benchmark program" );
	g_option_context_add_group( context, vips_get_option_group() );
	if( !g_option_context_parse( context, &argc, &argv, &error ) ) {
		if( error ) {
			fprintf( stderr, "%s\n", error->message );
			g_error_free( error );
		}

		vips_error_exit( NULL );
	}
	g_option_context_free( context );

        VImage in = VImage::new_from_file( argv[1] );

        VImage mask = VImage::new_matrixv( 3, 3, 
                -1, -1, -1, -1, 16, -1, -1, -1, -1 );
	mask.set( "scale", 8 ); 

        in.
                extract_area( 100, 100, in.width() - 200, in.height() - 200 ).
                similarity( VImage::option()->set( "scale", 0.9 ) ).
                conv( mask ). 
                write_to_file( argv[2] );

        return( 0 );
}
