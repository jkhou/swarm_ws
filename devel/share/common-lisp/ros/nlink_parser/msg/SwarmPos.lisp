; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude SwarmPos.msg.html

(cl:defclass <SwarmPos> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (swarm_pos
    :reader swarm_pos
    :initarg :swarm_pos
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 16 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass SwarmPos (<SwarmPos>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SwarmPos>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SwarmPos)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<SwarmPos> is deprecated: use nlink_parser-msg:SwarmPos instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <SwarmPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:header-val is deprecated.  Use nlink_parser-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'swarm_pos-val :lambda-list '(m))
(cl:defmethod swarm_pos-val ((m <SwarmPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:swarm_pos-val is deprecated.  Use nlink_parser-msg:swarm_pos instead.")
  (swarm_pos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SwarmPos>) ostream)
  "Serializes a message object of type '<SwarmPos>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'swarm_pos))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SwarmPos>) istream)
  "Deserializes a message object of type '<SwarmPos>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'swarm_pos) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'swarm_pos)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SwarmPos>)))
  "Returns string type for a message object of type '<SwarmPos>"
  "nlink_parser/SwarmPos")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SwarmPos)))
  "Returns string type for a message object of type 'SwarmPos"
  "nlink_parser/SwarmPos")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SwarmPos>)))
  "Returns md5sum for a message object of type '<SwarmPos>"
  "1c5deeae29fc99ca2d59a905d86e689d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SwarmPos)))
  "Returns md5sum for a message object of type 'SwarmPos"
  "1c5deeae29fc99ca2d59a905d86e689d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SwarmPos>)))
  "Returns full string definition for message of type '<SwarmPos>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[16] swarm_pos~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SwarmPos)))
  "Returns full string definition for message of type 'SwarmPos"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[16] swarm_pos~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SwarmPos>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'swarm_pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SwarmPos>))
  "Converts a ROS message object to a list"
  (cl:list 'SwarmPos
    (cl:cons ':header (header msg))
    (cl:cons ':swarm_pos (swarm_pos msg))
))
