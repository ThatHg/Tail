#ifndef PLATFORM_DETECTOR_H
#define PLATFORM_DETECTOR_H

#if defined( _WIN32 )

#elif defined( __linux )

#else

#error Platform not yet supported

#endif



#endif // !PLATFORM_DETECTOR_H
