#include <fstream>
#include <json.hpp>
#include <FrameInterpolation.hpp>


FrameInterpolation::FrameInterpolation(const std::string &filePath)
{
    std::ifstream f(filePath);
    nlohmann::json data = nlohmann::json::parse(f);

    for(const auto &entry : data)
    {
        _interpolationMap.emplace(entry["time"], toEigenTransform(entry["matrix"].get<std::vector<std::vector<double>>>()));
    }
    
    _deltaT = ((std::next(_interpolationMap.begin()))->first) - _interpolationMap.begin()->first;
}

Transform FrameInterpolation::operator()(double t)
{
    Eigen::Matrix4d result;
    t = t < _interpolationMap.begin()->first ? _interpolationMap.begin()->first : t;
    t = t > std::prev(_interpolationMap.end())->first ? std::prev(_interpolationMap.end())->first : t;

    auto it = std::find_if(_interpolationMap.begin(), _interpolationMap.end(),
        [&] (const auto &entry) -> bool
        {
            return t >= entry.first && t < entry.first + _deltaT;
        });
    
    const Transform m1 = it->second;
    const double t1 = it->first;
    const Transform m2 = std::next(it) == _interpolationMap.end() ? it->second : std::next(it)->second;
    const double t2 = std::next(it) == _interpolationMap.end() ? it->first : std::next(it)->first;
    
    const double progression = (t - t1) / (t2 - t1);
    
    result.block<3, 1>(0, 3) = m1.translation() + progression * (m2.translation() - m1.translation());

    const Eigen::AngleAxisd relativeAxisAngle = Eigen::AngleAxisd(m2.linear().transpose() * m1.linear());
    const Eigen::Vector3d axis = m2.linear() * relativeAxisAngle.axis();
    const Eigen::AngleAxisd progressedAxisAngle = Eigen::AngleAxisd(progression * relativeAxisAngle.angle(), axis);
    result.block<3, 3>(0, 0) = m1.linear() * progressedAxisAngle.toRotationMatrix();

    Transform progressedTransform;
    progressedTransform.matrix() = result;
    return progressedTransform;
}

Transform FrameInterpolation::toEigenTransform(const std::vector<std::vector<double>> &data)
{
    Eigen::Matrix4d mat;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            mat(i, j) = data[i][j];
        }
    }
    Transform t;
    t.matrix() = mat;
    return t;
}
