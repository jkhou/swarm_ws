; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude LinktrackNodeframe3.msg.html

(cl:defclass <LinktrackNodeframe3> (roslisp-msg-protocol:ros-message)
  ((role
    :reader role
    :initarg :role
    :type cl:fixnum
    :initform 0)
   (id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (local_time
    :reader local_time
    :initarg :local_time
    :type cl:integer
    :initform 0)
   (system_time
    :reader system_time
    :initarg :system_time
    :type cl:integer
    :initform 0)
   (voltage
    :reader voltage
    :initarg :voltage
    :type cl:float
    :initform 0.0)
   (nodes
    :reader nodes
    :initarg :nodes
    :type (cl:vector nlink_parser-msg:LinktrackNode2)
   :initform (cl:make-array 0 :element-type 'nlink_parser-msg:LinktrackNode2 :initial-element (cl:make-instance 'nlink_parser-msg:LinktrackNode2))))
)

(cl:defclass LinktrackNodeframe3 (<LinktrackNodeframe3>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinktrackNodeframe3>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinktrackNodeframe3)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<LinktrackNodeframe3> is deprecated: use nlink_parser-msg:LinktrackNodeframe3 instead.")))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:role-val is deprecated.  Use nlink_parser-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'local_time-val :lambda-list '(m))
(cl:defmethod local_time-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:local_time-val is deprecated.  Use nlink_parser-msg:local_time instead.")
  (local_time m))

(cl:ensure-generic-function 'system_time-val :lambda-list '(m))
(cl:defmethod system_time-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:system_time-val is deprecated.  Use nlink_parser-msg:system_time instead.")
  (system_time m))

(cl:ensure-generic-function 'voltage-val :lambda-list '(m))
(cl:defmethod voltage-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:voltage-val is deprecated.  Use nlink_parser-msg:voltage instead.")
  (voltage m))

(cl:ensure-generic-function 'nodes-val :lambda-list '(m))
(cl:defmethod nodes-val ((m <LinktrackNodeframe3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:nodes-val is deprecated.  Use nlink_parser-msg:nodes instead.")
  (nodes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinktrackNodeframe3>) ostream)
  "Serializes a message object of type '<LinktrackNodeframe3>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'local_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'local_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'local_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'local_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_time)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'voltage))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'nodes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'nodes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinktrackNodeframe3>) istream)
  "Deserializes a message object of type '<LinktrackNodeframe3>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'local_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'local_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'local_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'local_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'voltage) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'nodes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'nodes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nlink_parser-msg:LinktrackNode2))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinktrackNodeframe3>)))
  "Returns string type for a message object of type '<LinktrackNodeframe3>"
  "nlink_parser/LinktrackNodeframe3")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinktrackNodeframe3)))
  "Returns string type for a message object of type 'LinktrackNodeframe3"
  "nlink_parser/LinktrackNodeframe3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinktrackNodeframe3>)))
  "Returns md5sum for a message object of type '<LinktrackNodeframe3>"
  "d5fe6bc25d71efe36dc5d4595d69025e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinktrackNodeframe3)))
  "Returns md5sum for a message object of type 'LinktrackNodeframe3"
  "d5fe6bc25d71efe36dc5d4595d69025e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinktrackNodeframe3>)))
  "Returns full string definition for message of type '<LinktrackNodeframe3>"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint32 local_time~%uint32 system_time~%float32 voltage~%LinktrackNode2[] nodes~%~%================================================================================~%MSG: nlink_parser/LinktrackNode2~%uint8 role~%uint8 id~%float32 dis~%float32 fp_rssi~%float32 rx_rssi~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinktrackNodeframe3)))
  "Returns full string definition for message of type 'LinktrackNodeframe3"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint32 local_time~%uint32 system_time~%float32 voltage~%LinktrackNode2[] nodes~%~%================================================================================~%MSG: nlink_parser/LinktrackNode2~%uint8 role~%uint8 id~%float32 dis~%float32 fp_rssi~%float32 rx_rssi~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinktrackNodeframe3>))
  (cl:+ 0
     1
     1
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'nodes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinktrackNodeframe3>))
  "Converts a ROS message object to a list"
  (cl:list 'LinktrackNodeframe3
    (cl:cons ':role (role msg))
    (cl:cons ':id (id msg))
    (cl:cons ':local_time (local_time msg))
    (cl:cons ':system_time (system_time msg))
    (cl:cons ':voltage (voltage msg))
    (cl:cons ':nodes (nodes msg))
))
