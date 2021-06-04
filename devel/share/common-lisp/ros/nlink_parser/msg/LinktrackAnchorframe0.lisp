; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude LinktrackAnchorframe0.msg.html

(cl:defclass <LinktrackAnchorframe0> (roslisp-msg-protocol:ros-message)
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
    :type (cl:vector nlink_parser-msg:LinktrackTag)
   :initform (cl:make-array 0 :element-type 'nlink_parser-msg:LinktrackTag :initial-element (cl:make-instance 'nlink_parser-msg:LinktrackTag))))
)

(cl:defclass LinktrackAnchorframe0 (<LinktrackAnchorframe0>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinktrackAnchorframe0>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinktrackAnchorframe0)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<LinktrackAnchorframe0> is deprecated: use nlink_parser-msg:LinktrackAnchorframe0 instead.")))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:role-val is deprecated.  Use nlink_parser-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'local_time-val :lambda-list '(m))
(cl:defmethod local_time-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:local_time-val is deprecated.  Use nlink_parser-msg:local_time instead.")
  (local_time m))

(cl:ensure-generic-function 'system_time-val :lambda-list '(m))
(cl:defmethod system_time-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:system_time-val is deprecated.  Use nlink_parser-msg:system_time instead.")
  (system_time m))

(cl:ensure-generic-function 'voltage-val :lambda-list '(m))
(cl:defmethod voltage-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:voltage-val is deprecated.  Use nlink_parser-msg:voltage instead.")
  (voltage m))

(cl:ensure-generic-function 'nodes-val :lambda-list '(m))
(cl:defmethod nodes-val ((m <LinktrackAnchorframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:nodes-val is deprecated.  Use nlink_parser-msg:nodes instead.")
  (nodes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinktrackAnchorframe0>) ostream)
  "Serializes a message object of type '<LinktrackAnchorframe0>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinktrackAnchorframe0>) istream)
  "Deserializes a message object of type '<LinktrackAnchorframe0>"
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
    (cl:setf (cl:aref vals i) (cl:make-instance 'nlink_parser-msg:LinktrackTag))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinktrackAnchorframe0>)))
  "Returns string type for a message object of type '<LinktrackAnchorframe0>"
  "nlink_parser/LinktrackAnchorframe0")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinktrackAnchorframe0)))
  "Returns string type for a message object of type 'LinktrackAnchorframe0"
  "nlink_parser/LinktrackAnchorframe0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinktrackAnchorframe0>)))
  "Returns md5sum for a message object of type '<LinktrackAnchorframe0>"
  "cbcf3e0d7d7505d0e2909378d4beb301")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinktrackAnchorframe0)))
  "Returns md5sum for a message object of type 'LinktrackAnchorframe0"
  "cbcf3e0d7d7505d0e2909378d4beb301")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinktrackAnchorframe0>)))
  "Returns full string definition for message of type '<LinktrackAnchorframe0>"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint32 local_time~%uint32 system_time~%float32 voltage~%LinktrackTag[] nodes~%~%~%================================================================================~%MSG: nlink_parser/LinktrackTag~%uint8 role~%uint8 id~%float32[3] pos_3d~%float32[8] dis_arr~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinktrackAnchorframe0)))
  "Returns full string definition for message of type 'LinktrackAnchorframe0"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint32 local_time~%uint32 system_time~%float32 voltage~%LinktrackTag[] nodes~%~%~%================================================================================~%MSG: nlink_parser/LinktrackTag~%uint8 role~%uint8 id~%float32[3] pos_3d~%float32[8] dis_arr~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinktrackAnchorframe0>))
  (cl:+ 0
     1
     1
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'nodes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinktrackAnchorframe0>))
  "Converts a ROS message object to a list"
  (cl:list 'LinktrackAnchorframe0
    (cl:cons ':role (role msg))
    (cl:cons ':id (id msg))
    (cl:cons ':local_time (local_time msg))
    (cl:cons ':system_time (system_time msg))
    (cl:cons ':voltage (voltage msg))
    (cl:cons ':nodes (nodes msg))
))
