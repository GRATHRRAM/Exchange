#include <cstddef>
#include <cstdint>
#include <raylib.h>


class StartScreen {
    private:
        size_t *Seed;
        Rectangle TextBox;
        uint8_t MaxCharInput = 12;
    public:
        StartScreen(uint16_t ResX, uint16_t ResY, size_t *Seed);
        void Run();
};
