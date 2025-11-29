#include <iostream>
#include <FrameInterpolation.hpp>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <json_file_path> <time_instant>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    double timeInstant = std::stod(argv[2]);

    auto f = FrameInterpolation(filePath);
    auto t1 = f(timeInstant);

    std::cout << "Interpolated transform at t=" << timeInstant << ":\n" << t1.matrix() << std::endl;

    return 0;
}