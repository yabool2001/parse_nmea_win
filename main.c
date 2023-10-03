#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nmea_gngll_message[255] ;
char gngll[6] = "$GNGLL" ;
int n = 0 ;

/* Funkcja do parsowania wiadomości NMEA $GNGLL
** Synopsis:
** $<TalkerID>GLL,<Lat>,<N/S>,<Lon>,<E/W>,<UTC>,<Status>,<ModeInd>*<Checksum><CR><LF>
** Synopsis:
** $<TalkerID>GSA,<Mode>,<FixMode>,{<SatID>},<PDOP>,<HDOP>,<VDOP><SystemID>*<Checksum><CR><LF>
Parameter:
<Mode>:
    M = Manual, forced to operate in 2D or 3D mode
    A = Automatic, allowed to automatically switch to 2D/3D
<FixMode>:
    1 = Fix not available
    2 = 2D
    3 = 3D
<SatID>: IDs of satellites used in solution.
<PDOP>: Position dilution of precision. Maximum value: 99.0.
<HDOP>: Horizontal dilution of precision. Maximum value: 99.0.
<VDOP>: Vertical dilution of precision. Maximum value: 99.0.
<SystemID>: GNSS system ID.
*/
int my_nmea_message ( char* c , char* m , int* i )
{
    if ( *c == '$' )
    {
        *i = 0 ;
        m[(*i)++] = *c ;
        m[*i] = '\0' ;
        return 0 ;
    }
    if ( ( *c >= ' ' && *c <= '~' && *i > 0 ) || *c == '\r' )
    {
        m[(*i)++] = *c ;
        m[*i] = '\0' ;
        return 1 ;
    }
    if ( *c == '\n' && *i > 1 )
    {
        if ( m[--(*i)] == '\r' )
        {
            m[*i] = '\0' ;
            return 2 ;
        }
    }
    return -1 ;
}

int main ()
{
    char nmea_stream[] = "$GNCGA,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GPGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n";
    int i ;
    int l = strlen ( nmea_stream ) ;
    int r ;
    for ( i = 0 ; i < l ; i++ )
    {
        r = my_nmea_message ( &nmea_stream[i] , nmea_gngll_message , &n ) ;
        if ( r == 2 && !strncmp ( nmea_gngll_message , gngll , 6 ) )
        {
            printf ( nmea_gngll_message ) ;
        }
    }
    
    /*
    if (parseGNGLL(nmea, &latitude, &longitude) == 0) {
        printf("Szerokość geograficzna: %.4lf\n", latitude);
        printf("Długość geograficzna: %.4lf\n", longitude);
        printf("Wprowadź te dane do Google Maps: %.4lf, %.4lf\n", latitude, longitude);
    } else {
        printf("Błąd parsowania wiadomości NMEA.\n");
    }
    */
    return 0;
}
