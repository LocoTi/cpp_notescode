//
// Created by int.xuqian.zhu on 7/28/2021.
//

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <list>

/**
 * test shared_ptr 资源管理器
 */
namespace myspace {

class Feature;
class MapPoint;
class Frame {
public:
    typedef std::shared_ptr<Frame> PTR;
    Frame() = default;
    explicit Frame(long id, std::unordered_map<int, int>& pose)
        : id_(id), pose_(pose) {}
    ~Frame() {
        std::cout << "~Frame();" << std::endl;
    }

    long id_ = 0;
    std::unordered_map<int, int> pose_;

    std::mutex pose_mutex_;

    std::vector<std::shared_ptr<Feature>> features;

    std::unordered_map<int, int> Pose() {
        std::unique_lock<std::mutex> lck(pose_mutex_);
        return pose_;
    }

    void SetPose(const std::unordered_map<int, int>& pose) {
        std::unique_lock<std::mutex> lck(pose_mutex_);
        pose_ = pose;
    }

    /// 工厂构建模式，分配id
    static Frame::PTR CreateFrame();
};
Frame::PTR Frame::CreateFrame() {
    static long factory_id = 0;
    Frame::PTR new_frame(new Frame);
    new_frame->id_ = factory_id;
    return new_frame;
}

class Feature {
public:
    typedef std::shared_ptr<Feature> PTR;
    Feature() = default;
    explicit Feature(const std::shared_ptr<Frame>& frame)
            : frame_(frame) {}
    ~Feature() {
        std::cout << "~Feature();" << std::endl;
    }

    std::weak_ptr<Frame> frame_;
    std::weak_ptr<MapPoint> mappoint_;
};

class MapPoint {
public:
    typedef std::shared_ptr<MapPoint> PTR;
    MapPoint() = default;
    MapPoint(long id, std::unordered_map<int, int>& pos)
        : id_(id), pos_(pos){}
    ~MapPoint() {
        std::cout << "~MapPoint();" << std::endl;
    }

    long id_ = 0;
    std::unordered_map<int, int> pos_;

    std::mutex data_mutex_;

    std::list<std::weak_ptr<Feature>> observations_;

    std::unordered_map<int, int> Pos() {
        std::unique_lock<std::mutex> lck(data_mutex_);
        return pos_;
    }

    void SetPos(const std::unordered_map<int, int>& pos) {
        std::unique_lock<std::mutex> lck(data_mutex_);
        pos_ = pos;
    }

    void AddObservation(const std::shared_ptr<Feature>& feature) {
        std::unique_lock<std::mutex> lck(data_mutex_);
        observations_.push_back(feature);
    }

    std::list<std::weak_ptr<Feature>> GetObs() {
        std::unique_lock<std::mutex> lck(data_mutex_);
        return observations_;
    }

    // factory function
    static MapPoint::PTR CreateNewMappoint();
};

MapPoint::PTR MapPoint::CreateNewMappoint() {
    static long factor_id = 0;
    MapPoint::PTR new_mappoint(new MapPoint);
    new_mappoint->id_ = factor_id;
    return new_mappoint;
}

};  // namespace myspace

void test_shared_ptr1() {
    using namespace myspace;
    std::unordered_map<int, int> pose1;
    Frame::PTR frame1(new Frame(1, pose1));

    Feature::PTR feature1(new Feature(frame1));

    std::unordered_map<int, int> pos1;
    MapPoint::PTR mappoint1(new MapPoint(1, pos1));

    frame1->features.push_back(feature1);

    mappoint1->AddObservation(feature1);
}

void test_shared_ptr2() {
    using namespace myspace;
    Frame::PTR frame1 = Frame::CreateFrame();

    Feature::PTR feature1(new Feature(frame1));
    frame1->features.push_back(feature1);

    MapPoint::PTR map_point1 = MapPoint::CreateNewMappoint();
    map_point1->AddObservation(feature1);
}

int main() {
    test_shared_ptr1();

    test_shared_ptr2();
}