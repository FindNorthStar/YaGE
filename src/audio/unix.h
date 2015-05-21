#ifndef AUDIO_UNIX_H_
#define AUDIO_UNIX_H_
#include <string>
#include <gst/gst.h>
#include "player.h"

namespace yage {
namespace audio {

class UnixPlayer : public Player {
private:
  GstElement *pipeline_;
  GstBus *bus_;

  static gboolean bus_call(GstBus *bus, GstMessage *msg, void *user_data);

public:
	UnixPlayer(const std::string &url);
	virtual ~UnixPlayer();
	virtual bool play(void);
	virtual void pause(void);
	virtual void stop(void);
	virtual bool is_playing(void);
};

}
}

#endif /* end of include guard: LINUX_H_BQTYW1ZH */
