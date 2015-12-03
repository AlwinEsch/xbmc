# *<p align="center">Kodi development</p>*
#### *<p align="center">Group: ```Directory```</p>*

----------

Functions
-------------

The with ```#include <kodi/addon.api2/Directory.h``` given functions are basically used to allow add-on access to kodi's directory system.

*  <b>```bool CAddOnLib_Directory::CanOpenDirectory(const std::string& strUrl);```</b>
    * Checks whether a directory can be opened.
	    * <b>```strPath```</b> The URL of the directory to check.
		* <b>return:</b>  True when it can be opened, false otherwise.

*  <b>```bool CAddOnLib_Directory::CreateDirectory(const std::string& strPath);```</b>
    * Creates a directory.
	    * <b>```strPath```</b> Path to the directory.
		* <b>return:</b> True when it was created, false otherwise.

*  <b>```bool CAddOnLib_Directory::DirectoryExists(const std::string& strPath);```</b>
    * Checks if a directory exists.
	    * <b>```strPath```</b> Path to the directory.
		* <b>return:</b> True when it exists, false otherwise.

*  <b>```bool CAddOnLib_Directory::RemoveDirectory(const std::string& strPath);```</b>
    * Removes a directory.
	    * <b>```strPath```</b> Path to the directory.
		* <b>return:</b> True when it was removed, false otherwise.
