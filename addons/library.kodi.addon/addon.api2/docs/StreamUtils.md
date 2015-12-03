# *<p align="center">Kodi development</p>*
#### *<p align="center">Group: ```Stream utilities```</p>*

----------

The with #include ```<kodi/addon.api2/StreamUtils.h>``` given functions are basically used to allow add-on access to Kodi's functions

Classes
-------------

#### Class: ```CStreamProperties::CStreamProperties(...);```

*  <b>```CStreamProperties()```</b>
    * Constructor

*  <b>```virtual ~CStreamProperties();```</b>
    * Destructor

*  <b>```void Clear(void);```</b>
    * Resets the streams

*  <b>```int GetStreamId(unsigned int iPhysicalId) const;```</b>
    * Returns the index of the stream with the specified physical ID, or -1 if there no stream is found. This method is called very often which is why we keep a separate map for this.
	    * <b>```iPhysicalId```</b> Identifier for stream data to get
		* <b>return:</b>The used class id for it

* ```CPVRStream* GetStreamById(unsigned int iPhysicalId) const;```</b>
    * Returns the stream with the specified physical ID, or null if no such stream exists
	    * <b>```iPhysicalId```</b> Identifier for stream data to get
		* <b>return:</b> Return pointer of stream to get

*  <b>```void GetStreamData(unsigned int iPhysicalId, CPVRStream* stream);```</b>
    * Populates the specified stream with the stream having the specified physical ID. If the stream is not found only target stream's physical ID will be populated.
	    * <b>```iPhysicalId```</b> Identifier for stream data to get
	    * <b>```stream```</b> Return pointer of stream to get

*  <b>```bool GetProperties(PVR_STREAM_PROPERTIES* props);```</b>
    * Populates props with the current streams and returns whether there are any streams at the moment or not.
	    * <b>```props```</b>  Pointer where present properties becomes stored
		* <b>return:</b> True if success

*  <b>```void UpdateStreams(stream_vector &newStreams);```</b>
    *  Merges new streams into the current list of streams. Identical streams will retain their respective indexes and new streams will replace unused indexes or be appended.
	    * <b>```newStreams```</b>  Pointer to pass to set streams array

-------------
#### Class: ```CStreamProperties::CStreamProperties(...);```

*  <b>```CPVRStream()```</b>
    * Constructor

*  <b>```CPVRStream(const CPVRStream &other)```</b>
    * Constructor to generate copy of given class
    * 
*  <b>```~CPVRStream();```</b>
    * Destructor

*  <b>```bool operator==(const CPVRStream &other) const;```</b>
    * Compares this stream based on another stream
	    * <b>```other```</b>  The other stream to compare
		* <b>return:</b> true if equal
		* 
*  <b>``` bool operator<(const CPVRStream &other) const;```</b>
    * Compares this stream with another one so that video streams are sorted before any other streams and the others are sorted by the physical ID
	    * <b>```other```</b>  The other stream to compare
		* <b>return:</b> true if before

*  <b>```void Clear();```</b>
    * Clears the stream

*  <b>```bool IsCleared() const;```</b>
		* <b>return:</b> True if cleared
