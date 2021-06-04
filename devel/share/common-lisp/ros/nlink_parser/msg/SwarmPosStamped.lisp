; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude SwarmPosStamped.msg.html

(cl:defclass <SwarmPosStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (poses
    :reader poses
    :initarg :poses
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 4 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass SwarmPosStamped (<SwarmPosStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SwarmPosStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SwarmPosStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<SwarmPosStamped> is deprecated: use nlink_parser-msg:SwarmPosStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <SwarmPosStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:header-val is deprecated.  Use nlink_parser-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'poses-val :lambda-list '(m))
(cl:defmethod poses-val ((m <SwarmPosStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:poses-val is deprecated.  Use nlink_parser-msg:poses instead.")
  (poses m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SwarmPosStamped>) ostream)
  "Serializes a message object of type '<SwarmPosStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'poses))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SwarmPosStamped>) istream)
  "Deserializes a message object of type '<SwarmPosStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'poses) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'poses)))
    (cl:dotimes (i 4)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SwarmPosStamped>)))
  "Returns string type for a message object of type '<SwarmPosStamped>"
  "nlink_parser/SwarmPosStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SwarmPosStamped)))
  "Returns string type for a message object of type 'SwarmPosStamped"
  "nlink_parser/SwarmPosStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SwarmPosStamped>)))
  "Returns md5sum for a message object of type '<SwarmPosStamped>"
  "672cc37da9e1e0dee9bea324fba5efb7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SwarmPosStamped)))
  "Returns md5sum for a message object of type 'SwarmPosStamped"
  "672cc37da9e1e0dee9bea324fba5efb7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SwarmPosStamped>)))
  "Returns full string definition for message of type '<SwarmPosStamped>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[4] poses~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SwarmPosStamped)))
  "Returns full string definition for message of type 'SwarmPosStamped"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[4] poses~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SwarmPosStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'poses) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SwarmPosStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'SwarmPosStamped
    (cl:cons ':header (header msg))
    (cl:cons ':poses (poses msg))
))
