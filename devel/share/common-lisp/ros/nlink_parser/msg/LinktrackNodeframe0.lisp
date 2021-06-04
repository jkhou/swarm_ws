; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude LinktrackNodeframe0.msg.html

(cl:defclass <LinktrackNodeframe0> (roslisp-msg-protocol:ros-message)
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
   (nodes
    :reader nodes
    :initarg :nodes
    :type (cl:vector nlink_parser-msg:LinktrackNode0)
   :initform (cl:make-array 0 :element-type 'nlink_parser-msg:LinktrackNode0 :initial-element (cl:make-instance 'nlink_parser-msg:LinktrackNode0))))
)

(cl:defclass LinktrackNodeframe0 (<LinktrackNodeframe0>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinktrackNodeframe0>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinktrackNodeframe0)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<LinktrackNodeframe0> is deprecated: use nlink_parser-msg:LinktrackNodeframe0 instead.")))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <LinktrackNodeframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:role-val is deprecated.  Use nlink_parser-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LinktrackNodeframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'nodes-val :lambda-list '(m))
(cl:defmethod nodes-val ((m <LinktrackNodeframe0>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:nodes-val is deprecated.  Use nlink_parser-msg:nodes instead.")
  (nodes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinktrackNodeframe0>) ostream)
  "Serializes a message object of type '<LinktrackNodeframe0>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'nodes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'nodes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinktrackNodeframe0>) istream)
  "Deserializes a message object of type '<LinktrackNodeframe0>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'nodes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'nodes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nlink_parser-msg:LinktrackNode0))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinktrackNodeframe0>)))
  "Returns string type for a message object of type '<LinktrackNodeframe0>"
  "nlink_parser/LinktrackNodeframe0")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinktrackNodeframe0)))
  "Returns string type for a message object of type 'LinktrackNodeframe0"
  "nlink_parser/LinktrackNodeframe0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinktrackNodeframe0>)))
  "Returns md5sum for a message object of type '<LinktrackNodeframe0>"
  "99d2eee732fdf2fb898d64e9172d0e66")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinktrackNodeframe0)))
  "Returns md5sum for a message object of type 'LinktrackNodeframe0"
  "99d2eee732fdf2fb898d64e9172d0e66")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinktrackNodeframe0>)))
  "Returns full string definition for message of type '<LinktrackNodeframe0>"
  (cl:format cl:nil "uint8 role~%uint8 id~%LinktrackNode0[] nodes~%~%================================================================================~%MSG: nlink_parser/LinktrackNode0~%uint8 role~%uint8 id~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinktrackNodeframe0)))
  "Returns full string definition for message of type 'LinktrackNodeframe0"
  (cl:format cl:nil "uint8 role~%uint8 id~%LinktrackNode0[] nodes~%~%================================================================================~%MSG: nlink_parser/LinktrackNode0~%uint8 role~%uint8 id~%uint8[] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinktrackNodeframe0>))
  (cl:+ 0
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'nodes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinktrackNodeframe0>))
  "Converts a ROS message object to a list"
  (cl:list 'LinktrackNodeframe0
    (cl:cons ':role (role msg))
    (cl:cons ':id (id msg))
    (cl:cons ':nodes (nodes msg))
))
