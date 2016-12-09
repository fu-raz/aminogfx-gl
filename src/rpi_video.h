#ifndef _AMINO_RPI_VIDEO_H
#define _AMINO_RPI_VIDEO_H

#include "base.h"

extern "C" {
    #include "ilclient/ilclient.h"
    #include "EGL/eglext.h"
}

/**
 * Abstract video stream.
 */
class AnyVideoStream {
public:
    AnyVideoStream();
    virtual ~AnyVideoStream();

    virtual bool init() = 0;

    virtual bool endOfStream() = 0;
    virtual bool rewind() = 0;

    std:string getLastError();
protected:
    std::string lastError;
}

/**
 * Video file stream.
 */
class VideoFileStream : public AnyVideoStream {
public:
    VideoFileStream(std::string filename);
    ~VideoFileStream();

private:
    std::string filename;
    FILE *file = NULL;

    bool init() override;

    bool endOfStream() override;
    bool rewind() override;
}

/**
 * OMX Video Player.
 */
class AminoOmxVideoPlayer : public AminoVideoPlayer {
public:
    AminoOmxVideoPlayer(AminoTexture *texture, AminoVideo *video);

    void init() override;
    bool initTexture();

    //stream
    bool initStream();

    //OMX
    static void omxThread(void *arg);
    static void handleFillBufferDone(void *data, COMPONENT_T *comp);
    bool initOmx();
    void destroyOmx();

    static void initVideoTexture(AsyncValueUpdate *update, int state) {
    static void textureThread(void *arg);
    bool useTexture();

private:
    void *eglImage = NULL;
    ILCLIENT_T *client = NULL;
    AnyVideoStream *stream = NULL;

    uv_thread_t thread;
    bool threadRunning = false;

    TUNNEL_T tunnel[4];
    COMPONENT_T *list[5];
    bool omxInitialized = false;

public:
    COMPONENT_T *egl_render = NULL;
    OMX_BUFFERHEADERTYPE *eglBuffer = NULL;
    bool bufferError = false;
};

#endif