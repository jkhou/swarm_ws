; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude LinktrackNode0.msg.html

(cl:defclass <LinktrackNode0> (roslisp-msg-protocol:ros-message)
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
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass LinktrackNode0 (<LinktrackNode0>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinktrackNode0>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinktrackNode0)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<LinktrackNode0> is deprecated: use nlink_parser-msg:LinktrackNode0 instead.")))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <LinktrackNode0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:role-val is deprecated.  Use nlink_parser-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LinktrackNode0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <LinktrackNode0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:data-val is deprecated.  Use nlink_parser-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinktrackNode0>) ostream)
  "Serializes a message object of type '<LinktrackNode0>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinktrackNode0>) istream)
  "Deserializes a message object of type '<LinktrackNode0>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinktrackNode0>)))
  "Returns string type for a message object of type '<LinktrackNode0>"
  "nlink_parser/LinktrackNode0")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinktrackNode0)))
  "Returns string type for a message object of type 'LinktrackNode0"
  "nlink_parser/LinktrackNode0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinktrackNode0>)))
  "Returns md5sum for a message object of type '<LinktrackNode0>"
  "039fd4e4d2076d4b4621aa4a72ea3366")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinktrackNode0)))
  "Returns md5sum for a message object of type 'LinktrackNode0"
  "039fd4e4d2076d4b4621aa4a72ea3366")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinktrackNode0>)))
  "Returns full string definition for message of type '<LinktrackNode0>"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinktrackNode0)))
  "Returns full string definition for message of type 'LinktrackNode0"
  (cl:format cl:nil "uint8 role~%uint8 id~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinktrackNode0>))
  (cl:+ 0
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinktrackNode0>))
  "Converts a ROS message object to a list"
  (cl:list 'LinktrackNode0
    (cl:cons ':role (role msg))
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
