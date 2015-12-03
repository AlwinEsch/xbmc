# *<p align="center">Kodi development</p>*
#### *<p align="center">Group: ```Network```</p>*

----------

Functions
-------------

The with ```#include <kodi/addon.api2/Network.h>``` given functions are basically used to allow add-on access to Kodi's network functions

*  <b>```bool CAddOnLib_Network::WakeOnLan(const char* mac);```</b>
    * Send WakeOnLan magic packet.
	    * <b>```mac```</b> Network address of the host to wake.
		* <b>return:</b> True if the magic packet was successfully sent, false otherwise.

*  <b>```std::string CAddOnLib_Network::GetIPAddress();```</b>
    * Returns the current IP address as a string.
		* <b>return:</b> The ip.

*  <b>```std::string CAddOnLib_Network::URLEncode(const std::string& url);```</b>
    * Encode an URL
	    * <b>```url```</b> The code of the message to get.
		* <b>return:</b> Encoded URL string

*  <b>```bool CAddOnLib_Network::DNSLookup(const std::string& strHostName, std::string& strIpAddress);```</b>
    * Lookup URL in DNS cache
	    * <b>```strHostName```</b>The code of the message to get.
	    * <b>```strIpAddress```</b>Returned address
		* <b>return:</b> true if successful
