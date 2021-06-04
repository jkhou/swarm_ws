; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude TofsenseFrame0.msg.html

(cl:defclass <TofsenseFrame0> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (system_time
    :reader system_time
    :initarg :system_time
    :type cl:integer
    :initform 0)
   (dis
    :reader dis
    :initarg :dis
    :type cl:float
    :initform 0.0)
   (dis_status
    :reader dis_status
    :initarg :dis_status
    :type cl:fixnum
    :initform 0)
   (signal_strength
    :reader signal_strength
    :initarg :signal_strength
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TofsenseFrame0 (<TofsenseFrame0>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TofsenseFrame0>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TofsenseFrame0)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<TofsenseFrame0> is deprecated: use nlink_parser-msg:TofsenseFrame0 instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <TofsenseFrame0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'system_time-val :lambda-list '(m))
(cl:defmethod system_time-val ((m <TofsenseFrame0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:system_time-val is deprecated.  Use nlink_parser-msg:system_time instead.")
  (system_time m))

(cl:ensure-generic-function 'dis-val :lambda-list '(m))
(cl:defmethod dis-val ((m <TofsenseFrame0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:dis-val is deprecated.  Use nlink_parser-msg:dis instead.")
  (dis m))

(cl:ensure-generic-function 'dis_status-val :lambda-list '(m))
(cl:defmethod dis_status-val ((m <TofsenseFrame0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:dis_status-val is deprecated.  Use nlink_parser-msg:dis_status instead.")
  (dis_status m))

(cl:ensure-generic-function 'signal_strength-val :lambda-list '(m))
(cl:defmethod signal_strength-val ((m <TofsenseFrame0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:signal_strength-val is deprecated.  Use nlink_parser-msg:signal_strength instead.")
  (signal_strength m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TofsenseFrame0>) ostream)
  "Serializes a message object of type '<TofsenseFrame0>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_time)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_time)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dis))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dis_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'signal_strength)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'signal_strength)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TofsenseFrame0>) istream)
  "Deserializes a message object of type '<TofsenseFrame0>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'system_time)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dis) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dis_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'signal_strength)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'signal_strength)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TofsenseFrame0>)))
  "Returns string type for a message object of type '<TofsenseFrame0>"
  "nlink_parser/TofsenseFrame0")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TofsenseFrame0)))
  "Returns string type for a message object of type 'TofsenseFrame0"
  "nlink_parser/TofsenseFrame0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TofsenseFrame0>)))
  "Returns md5sum for a message object of type '<TofsenseFrame0>"
  "f4da8cb7f97b8a39238865249f6b98ed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TofsenseFrame0)))
  "Returns md5sum for a message object of type 'TofsenseFrame0"
  "f4da8cb7f97b8a39238865249f6b98ed")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TofsenseFrame0>)))
  "Returns full string definition for message of type '<TofsenseFrame0>"
  (cl:format cl:nil "uint8 id~%uint32 system_time~%float32 dis~%uint8 dis_status~%uint16 signal_strength~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TofsenseFrame0)))
  "Returns full string definition for message of type 'TofsenseFrame0"
  (cl:format cl:nil "uint8 id~%uint32 system_time~%float32 dis~%uint8 dis_status~%uint16 signal_strength~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TofsenseFrame0>))
  (cl:+ 0
     1
     4
     4
     1
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TofsenseFrame0>))
  "Converts a ROS message object to a list"
  (cl:list 'TofsenseFrame0
    (cl:cons ':id (id msg))
    (cl:cons ':system_time (system_time msg))
    (cl:cons ':dis (dis msg))
    (cl:cons ':dis_status (dis_status msg))
    (cl:cons ':signal_strength (signal_strength msg))
))
