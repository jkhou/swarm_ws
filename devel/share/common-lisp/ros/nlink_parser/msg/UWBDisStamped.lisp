; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude UWBDisStamped.msg.html

(cl:defclass <UWBDisStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (distance
    :reader distance
    :initarg :distance
    :type (cl:vector cl:float)
   :initform (cl:make-array 4 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass UWBDisStamped (<UWBDisStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <UWBDisStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'UWBDisStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<UWBDisStamped> is deprecated: use nlink_parser-msg:UWBDisStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <UWBDisStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:header-val is deprecated.  Use nlink_parser-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <UWBDisStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:distance-val is deprecated.  Use nlink_parser-msg:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <UWBDisStamped>) ostream)
  "Serializes a message object of type '<UWBDisStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'distance))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <UWBDisStamped>) istream)
  "Deserializes a message object of type '<UWBDisStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'distance) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'distance)))
    (cl:dotimes (i 4)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<UWBDisStamped>)))
  "Returns string type for a message object of type '<UWBDisStamped>"
  "nlink_parser/UWBDisStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'UWBDisStamped)))
  "Returns string type for a message object of type 'UWBDisStamped"
  "nlink_parser/UWBDisStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<UWBDisStamped>)))
  "Returns md5sum for a message object of type '<UWBDisStamped>"
  "2e9778231341331f56c760171dbc8c3f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'UWBDisStamped)))
  "Returns md5sum for a message object of type 'UWBDisStamped"
  "2e9778231341331f56c760171dbc8c3f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<UWBDisStamped>)))
  "Returns full string definition for message of type '<UWBDisStamped>"
  (cl:format cl:nil "std_msgs/Header header~%float64[4] distance~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'UWBDisStamped)))
  "Returns full string definition for message of type 'UWBDisStamped"
  (cl:format cl:nil "std_msgs/Header header~%float64[4] distance~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <UWBDisStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'distance) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <UWBDisStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'UWBDisStamped
    (cl:cons ':header (header msg))
    (cl:cons ':distance (distance msg))
))
