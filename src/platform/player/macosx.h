#ifndef PLAYER_MACOSX_H_
#define PLAYER_MACOSX_H_

#include "../player.h"

#ifdef __OBJC__
@class AVPlayer;
#else
struct AVPlayer;
#error An Objective-C++ compiler is required. Add "-ObjC++" in your CFLAGS and "-framework Foundation -framework AVFoundation" in your LDFLAGS.
#endif

namespace yage {
namespace platform {
class OSXPlayer : public Player {
    private:
        AVPlayer *player_;
        bool online_play_;
    public:
        OSXPlayer(std::string url);
        virtual ~OSXPlayer();
        virtual bool play();
        virtual void pause();
        virtual void stop();
        virtual bool is_playing();
};

}
}

#endif