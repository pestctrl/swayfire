#ifndef SWAYFIRE_PLUGIN_HPP
#define SWAYFIRE_PLUGIN_HPP

#include <wayfire/nonstd/observer_ptr.h>
#include <wayfire/object.hpp>
#include <wayfire/output.hpp>
#include <wayfire/per-output-plugin.hpp>
#include "signals.hpp"

class Swayfire;
using SwayfireRef = nonstd::observer_ptr<Swayfire>;

/// Reference to swayfire stored in the output.
struct SwayfireCustomData : public wf::custom_data_t {
    SwayfireRef swayfire;
    SwayfireCustomData(SwayfireRef swayfire) : swayfire(swayfire) {}
};

/// Utilities for swayfire plugins loaded through swayfire.
class SwayfirePlugin : public wf::per_output_plugin_instance_t {
  private:
    /// Whether swf_fini() was run yet.
    bool has_finished = false;

    wf::signal::connection_t<SwayfireInit> on_swayfire_init = [&](SwayfireInit *) {
        swayfire =
            output->get_data<SwayfireCustomData>("swayfire-core")->swayfire;
        swf_init();
    };

    wf::signal::connection_t<SwayfireFinish> on_swayfire_fini = [&](SwayfireFinish *) {
        assert(!has_finished);
        output->disconnect_signal(&on_swayfire_init);
        output->disconnect_signal(&on_swayfire_fini);
        swf_fini();
        has_finished = true;
    };

  public:
    /// Pointer to the active Swayfire plugin on this output.
    SwayfireRef swayfire = nullptr;

    /// Run plugin initialization. This is guaranteed to run after swayfire
    /// core's init.
    virtual void swf_init() = 0;

    /// Shut down plugin. This runs right before swayfire core's fini.
    virtual void swf_fini(){};

    // == Impl wf::plugin_interface_t ==
    void init() final {
        if (output->get_data<SwayfireCustomData>("swayfire-core"))
            on_swayfire_init.emit(nullptr);
        else
            output->connect(&on_swayfire_init);

        output->connect(&on_swayfire_fini);
    }
    void fini() final {
        if (!has_finished)
            on_swayfire_fini.emit(nullptr);
    }
};

#endif // SWAYFIRE_PLUGIN_HPP
