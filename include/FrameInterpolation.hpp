#include <map>
#include <vector>
#include <Eigen/Dense>

typedef Eigen::Transform<double, 3, Eigen::Affine> Transform;

class FrameInterpolation
{
public: 
    FrameInterpolation(const std::string& filePath);

    Transform operator()(double t);

private:
    Transform toEigenTransform(const std::vector<std::vector<double>> &data);

private:
    std::map<double, Transform> _interpolationMap;
    double _deltaT;
    int _lastQuery = 0;
};