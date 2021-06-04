// Generated by gencpp from file nlink_parser/SwarmInfoStamped.msg
// DO NOT EDIT!


#ifndef NLINK_PARSER_MESSAGE_SWARMINFOSTAMPED_H
#define NLINK_PARSER_MESSAGE_SWARMINFOSTAMPED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>

namespace nlink_parser
{
template <class ContainerAllocator>
struct SwarmInfoStamped_
{
  typedef SwarmInfoStamped_<ContainerAllocator> Type;

  SwarmInfoStamped_()
    : header()
    , poses()
    , vel()  {
    }
  SwarmInfoStamped_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , poses()
    , vel()  {
  (void)_alloc;
      poses.assign( ::geometry_msgs::Point_<ContainerAllocator> (_alloc));

      vel.assign( ::geometry_msgs::Point_<ContainerAllocator> (_alloc));
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array< ::geometry_msgs::Point_<ContainerAllocator> , 16>  _poses_type;
  _poses_type poses;

   typedef boost::array< ::geometry_msgs::Point_<ContainerAllocator> , 4>  _vel_type;
  _vel_type vel;





  typedef boost::shared_ptr< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> const> ConstPtr;

}; // struct SwarmInfoStamped_

typedef ::nlink_parser::SwarmInfoStamped_<std::allocator<void> > SwarmInfoStamped;

typedef boost::shared_ptr< ::nlink_parser::SwarmInfoStamped > SwarmInfoStampedPtr;
typedef boost::shared_ptr< ::nlink_parser::SwarmInfoStamped const> SwarmInfoStampedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator1> & lhs, const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.poses == rhs.poses &&
    lhs.vel == rhs.vel;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator1> & lhs, const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace nlink_parser

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "13aee0f85f95ab4c91a15c97f46b7cc3";
  }

  static const char* value(const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x13aee0f85f95ab4cULL;
  static const uint64_t static_value2 = 0x91a15c97f46b7cc3ULL;
};

template<class ContainerAllocator>
struct DataType< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nlink_parser/SwarmInfoStamped";
  }

  static const char* value(const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"geometry_msgs/Point[16] poses\n"
"geometry_msgs/Point[4] vel\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
;
  }

  static const char* value(const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.poses);
      stream.next(m.vel);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SwarmInfoStamped_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nlink_parser::SwarmInfoStamped_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nlink_parser::SwarmInfoStamped_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "poses[]" << std::endl;
    for (size_t i = 0; i < v.poses.size(); ++i)
    {
      s << indent << "  poses[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "    ", v.poses[i]);
    }
    s << indent << "vel[]" << std::endl;
    for (size_t i = 0; i < v.vel.size(); ++i)
    {
      s << indent << "  vel[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "    ", v.vel[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NLINK_PARSER_MESSAGE_SWARMINFOSTAMPED_H
