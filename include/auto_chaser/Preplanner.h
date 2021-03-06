#include "auto_chaser/Common.h"


class Preplanner{

    private:
        // params
        chaser::PreplannerParams params;
        string world_frame_id;
        // grid fields 
        vector<shared_ptr<GridField>> vsf_field_ptr_seq; // visibility score field sequence 
        Graph di_graph; // directed graph for preplanning 
        DescriptorMap descriptor_map;

        // ros 
        ros::Publisher pub_vsf_vis; // vsf field pub
        ros::Publisher pub_preplanned_path;  
        ros::Publisher pub_waypoints; 

        // markers
        visualization_msgs::Marker markers_visibility_field_base;
        visualization_msgs::MarkerArray markers_visibility_field_seq;
        visualization_msgs::Marker marker_wpnts; // waypoints of preplanned path
        
        // path 
        nav_msgs::Path preplanned_path; // for visualization and path completion 

        // subroutine functions
        VertexPath dijkstra(Vertex_d v0,Vertex_d vf);
        FieldParams get_local_vsf_param_around_target(Point target_pnt); // generate grid field based on the preplanning params        
        void compute_visibility_field_seq(GridField* global_edf,vector<Point> target_pnts); // local vsf seq generation 
        void graph_construct( GridField* global_edf,Point x0); // complete di_graph from vsf seq        
        
        // from dijkstra solution to real path and marker update   
        void compute_shortest_path();   

        
    public:
        Preplanner();
        void init(ros::NodeHandle nh);
        void preplan(GridField* global_edf_ptr,vector<Point> target_pnts,Point chaser_init);
        void publish();
        nav_msgs::Path get_preplanned_waypoints();
};