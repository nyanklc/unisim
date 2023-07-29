#include "vuniverse_engine.h"
#include "vuniverse_window.h"
#include "vuniverse_pipeline.h"

#include <memory>
#include <iostream>

using namespace vuniverse;

const int constexpr WIDTH = 800;
const int constexpr HEIGHT = 600;
const std::string WINDOW_TITLE = "Vuniverse Demo";

const std::string VERT_FILEPATH = "simpleshader.vert";
const std::string FRAG_FILEPATH = "simpleshader.frag";

int main() {

    // engine
    VuniverseEngine engine;

    // graphics
    std::unique_ptr<VuniverseWindow> window = std::make_unique<VuniverseWindow>(WIDTH, HEIGHT, WINDOW_TITLE);
    std::unique_ptr<VuniverseDevice> device = std::make_unique<VuniverseDevice>(*window);
    auto pipelineConfigInfo = VuniversePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT);
    VuniversePipeline pipeline(device.get(), VERT_FILEPATH, FRAG_FILEPATH, &pipelineConfigInfo);

    // initialize
    engine.start();
    window->initialize();

    while (engine.isRunning())
    {
        window->pollEvents();
        if (window->shouldClose())
        {
            engine.stop();
            break;
        }
    }

    window.reset();

    return EXIT_SUCCESS;
}