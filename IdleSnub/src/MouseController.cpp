#include "../headers/MouseController.h"



MouseController::MouseController()
{
    srand(static_cast<unsigned>(time(nullptr)));
}

void MouseController::MoveMouse(int& scrennWidth, int& screenHight)
{
    this->scrennWidth = scrennWidth;
    this->screenHight = screenHight;

    // Get a random mouse position on the screen
    RandomPoint pos =  GetRandomMousePosition();
    _randomScreenWidth = pos.x; //width
    _randomScreenHight = pos.y; //Highet

    // Move the mouse to the random position
    MouseMove(_randomScreenWidth, _randomScreenHight);
}


/*
 * Function that takes in the screen width and height and returns the random value.
 * It requiers a pointer to the x and y value of the screen.
 */
MouseController::RandomPoint MouseController::GetRandomMousePosition()
{
    RandomPoint p;
    p.x = rand() % scrennWidth;
    p.y = rand() % screenHight;
    return p;
}

void MouseController::MouseMove(const int& targetX, const int& targetY)
{
    // std::random_device is a class that provides a non-deterministic random number generator, utilizing hardware sources when available, to produce random numbers.
    static std::random_device g_rd;
    //std::mt19937 is a pseudorandom number generator based on the Mersenne Twister algorithm, specifically designed to produce high-quality random numbers with a period of 2^19937-1.
    static std::mt19937 g_gen(g_rd());
    // std::uniform_int_distribution is a class template that produces random integers uniformly distributed over a specified range.
    static std::uniform_int_distribution<int> g_jitter(-2, 2);

    POINT currentMousePos;
    GetCursorPos(&currentMousePos);

    // Control point for B�zier curve (midpoint + random offset)
    const POINT control = {
        (currentMousePos.x + targetX) / 2 + g_jitter(g_gen), 
        (currentMousePos.y + targetY) / 2 + g_jitter(g_gen)
    };

    const POINT target = { targetX, targetY };

    // Calculate movement steps based on distance
    const double dx = static_cast<double>(targetX - currentMousePos.x);
    const double dy = static_cast<double>(targetY - currentMousePos.y);
    const double distance = std::sqrt(dx * dx + dy * dy);
    const int numSteps = static_cast<int>(std::max<double>(distance / 10.0, 1.0));

    MouseInterpolates _MouseInterpolates;

    for (int i = 0; i <= numSteps; ++i) {
        const double t = static_cast<double>(i) / numSteps;
        // Ease-in/ease-out timing
        const double easeT = 0.5 - 0.5 * cos(t * M_PI);


        POINT pos = _MouseInterpolates.BezierInterpolate(currentMousePos, control, target, easeT);

        // Add small random jitter to simulate hand tremor
        SetCursorPos(pos.x + g_jitter(g_gen), pos.y + g_jitter(g_gen));

        // Variable sleep for more realism
        Sleep(3 + rand() % 4);
    }

    SetCursorPos(targetX, targetY);
}
