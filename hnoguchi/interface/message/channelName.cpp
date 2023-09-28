/*
 * 
 * channel    =  ( "#" / "+" / ( "!" channelid ) / "&" ) chanstring [ ":" chanstring ]
 *
 * chanstring =  %x01-07 / %x08-09 / %x0B-0C / %x0E-1F / %x21-2B
 * chanstring =/ %x2D-39 / %x3B-FF													; any octet except NUL, BELL, CR, LF, " ", "," and ":"
 * channelid  = 5( %x41-5A / digit )   ; 5( A-Z / 0-9 )
 * digit      =  %x30-39                 ; 0-9
 */

bool	validateChannelName(const std::string& name)
{
	return (true);
}
