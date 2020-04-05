#include <gazebo/gazebo.hh>

namespace gazebo {
  class WorldPluginMyRobot : public WorldPlugin {
    public: WorldPluginMyRobot() : WorldPlugin() {
              printf("Welcome to Joey's world!\n");
              printf("Hope you have fun here!\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf){
            }
  };
  
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)
}
