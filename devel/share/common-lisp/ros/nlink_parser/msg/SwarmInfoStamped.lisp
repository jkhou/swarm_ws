; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude SwarmInfoStamped.msg.html

(cl:defclass <SwarmInfoStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (poses
    :reader poses
    :initarg :poses
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 16 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (vel
    :reader vel
    :initarg :vel
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 4 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass SwarmInfoStamped (<SwarmInfoStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SwarmInfoStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SwarmInfoStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<SwarmInfoStamped> is deprecated: use nlink_parser-msg:SwarmInfoStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <SwarmInfoStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:header-val is deprecated.  Use nlink_parser-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'poses-val :lambda-list '(m))
(cl:defmethod poses-val ((m <SwarmInfoStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:poses-val is deprecated.  Use nlink_parser-msg:poses instead.")
  (poses m))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <SwarmInfoStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:vel-val is deprecated.  Use nlink_parser-msg:vel instead.")
  (vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SwarmInfoStamped>) ostream)
  "Serializes a message object of type '<SwarmInfoStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'poses))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'vel))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SwarmInfoStamped>) istream)
  "Deserializes a message object of type '<SwarmInfoStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'poses) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'poses)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  (cl:setf (cl:slot-value msg 'vel) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'vel)))
    (cl:dotimes (i 4)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SwarmInfoStamped>)))
  "Returns string type for a message object of type '<SwarmInfoStamped>"
  "nlink_parser/SwarmInfoStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SwarmInfoStamped)))
  "Returns string type for a message object of type 'SwarmInfoStamped"
  "nlink_parser/SwarmInfoStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SwarmInfoStamped>)))
  "Returns md5sum for a message object of type '<SwarmInfoStamped>"
  "13aee0f85f95ab4c91a15c97f46b7cc3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SwarmInfoStamped)))
  "Returns md5sum for a message object of type 'SwarmInfoStamped"
  "13aee0f85f95ab4c91a15c97f46b7cc3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SwarmInfoStamped>)))
  "Returns full string definition for message of type '<SwarmInfoStamped>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[16] poses~%geometry_msgs/Point[4] vel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SwarmInfoStamped)))
  "Returns full string definition for message of type 'SwarmInfoStamped"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[16] poses~%geometry_msgs/Point[4] vel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SwarmInfoStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'poses) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'vel) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SwarmInfoStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'SwarmInfoStamped
    (cl:cons ':header (header msg))
    (cl:cons ':poses (poses msg))
    (cl:cons ':vel (vel msg))
))
