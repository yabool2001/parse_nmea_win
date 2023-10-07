#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double nmea2decimal ( const char* , char ) ;

char nmea_message[255] ;
char nmea_gngll_message[255] ;
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

int main ()
{
    char nmea_stream[] = "$GNCGA,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GNGSA,A,3,12,19,32,06,11,28,,,,,,,1.69,1.42,0.91,1*06\r\n$GPGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n";
    // strtok ()
    const char* latitude = "5216.7071" ;
    char lat_dir = "N";
    const char* longitude = "02048.5512" ;
    char long_dir = "E" ;
    double lat = nmea2decimal ( latitude , lat_dir ) ;
    double lon = nmea2decimal ( longitude , long_dir ) ;
    return 0;
}

// Function to convert NMEA coordinates to decimal degrees
double nmea2decimal ( const char *coord , char direction )
{
    double degrees, minutes;
    sscanf(coord, "%lf", &degrees);
    minutes = degrees / 100;
    degrees = (int)minutes;
    minutes = minutes - degrees;
    return degrees + minutes / 0.6 * ((direction == 'S' || direction == 'W') ? -1 : 1);
}