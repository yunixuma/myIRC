/*
 * RFC-2812: Internet Relay Chat: Client Protocol
 *    2.3.1: Message format in Augmented BNF
 *
 * message    = [ ":" prefix SPACE ] command [ params ] crlf
 *
 * prefix     = servername / ( nickname [ [ "!" user ] "@" host ] )
 *
 * command    = 1*letter / 3digit
 *
 * params     = *14( SPACE middle ) [ SPACE ":" trailing ]
 *            = / 14( SPACE middle ) [ SPACE [ ":" ] trailing ]
 *
 * nospcrlfcl = %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF ; any octet except NUL, CR, LF, " " and ":"
 *
 * middle     =  nospcrlfcl *( ":" / nospcrlfcl )
 * trailing   =  *( ":" / " " / nospcrlfcl )
 * SPACE      =  %x20        									; space character
 * crlf       =  %x0D %x0A   									; "carriage return" "linefeed"
 */

