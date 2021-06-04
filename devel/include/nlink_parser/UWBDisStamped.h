// Generated by gencpp from file nlink_parser/UWBDisStamped.msg
// DO NOT EDIT!


#ifndef NLINK_PARSER_MESSAGE_UWBDISSTAMPED_H
#define NLINK_PARSER_MESSAGE_UWBDISSTAMPED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace nlink_parser
{
template <class ContainerAllocator>
struct UWBDisStamped_
{
  typedef UWBDisStamped_<ContainerAllocator> Type;

  UWBDisStamped_()
    : header()
    , distance()  {
      distance.assign(0.0);
  }
  UWBDisStamped_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , distance()  {
  (void)_alloc;
      distance.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array<double, 4>  _distance_type;
  _distance_type distance;





  typedef boost::shared_ptr< ::nlink_parser::UWBDisStamped_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nlink_parser::UWBDisStamped_<ContainerAllocator> const> ConstPtr;

}; // struct UWBDisStamped_

typedef ::nlink_parser::UWBDisStamped_<std::allocator<void> > UWBDisStamped;

typedef boost::shared_ptr< ::nlink_parser::UWBDisStamped > UWBDisStampedPtr;
typedef boost::shared_ptr< ::nlink_parser::UWBDisStamped const> UWBDisStampedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nlink_parser::UWBDisStamped_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::nlink_parser::UWBDisStamped_<ContainerAllocator1> & lhs, const ::nlink_parser::UWBDisStamped_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.distance == rhs.distance;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::nlink_parser::UWBDisStamped_<ContainerAllocator1> & lhs, const ::nlink_parser::UWBDisStamped_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace nlink_parser

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nlink_parser::UWBDisStamped_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nlink_parser::UWBDisStamped_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nlink_parser::UWBDisStamped_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "2e9778231341331f56c760171dbc8c3f";
  }

  static const char* value(const ::nlink_parser::UWBDisStamped_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x2e9778231341331fULL;
  static const uint64_t static_value2 = 0x56c760171dbc8c3fULL;
};

template<class ContainerAllocator>
struct DataType< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nlink_parser/UWBDisStamped";
  }

  static const char* value(const ::nlink_parser::UWBDisStamped_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"float64[4] distance\n"
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
;
  }

  static const char* value(const ::nlink_parser::UWBDisStamped_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.distance);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct UWBDisStamped_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nlink_parser::UWBDisStamped_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nlink_parser::UWBDisStamped_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "distance[]" << std::endl;
    for (size_t i = 0; i < v.distance.size(); ++i)
    {
      s << indent << "  distance[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.distance[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NLINK_PARSER_MESSAGE_UWBDISSTAMPED_H
