; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude TofsenseCascade.msg.html

(cl:defclass <TofsenseCascade> (roslisp-msg-protocol:ros-message)
  ((nodes
    :reader nodes
    :initarg :nodes
    :type (cl:vector nlink_parser-msg:TofsenseFrame0)
   :initform (cl:make-array 0 :element-type 'nlink_parser-msg:TofsenseFrame0 :initial-element (cl:make-instance 'nlink_parser-msg:TofsenseFrame0))))
)

(cl:defclass TofsenseCascade (<TofsenseCascade>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TofsenseCascade>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TofsenseCascade)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<TofsenseCascade> is deprecated: use nlink_parser-msg:TofsenseCascade instead.")))

(cl:ensure-generic-function 'nodes-val :lambda-list '(m))
(cl:defmethod nodes-val ((m <TofsenseCascade>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:nodes-val is deprecated.  Use nlink_parser-msg:nodes instead.")
  (nodes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TofsenseCascade>) ostream)
  "Serializes a message object of type '<TofsenseCascade>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'nodes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'nodes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TofsenseCascade>) istream)
  "Deserializes a message object of type '<TofsenseCascade>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'nodes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'nodes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nlink_parser-msg:TofsenseFrame0))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TofsenseCascade>)))
  "Returns string type for a message object of type '<TofsenseCascade>"
  "nlink_parser/TofsenseCascade")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TofsenseCascade)))
  "Returns string type for a message object of type 'TofsenseCascade"
  "nlink_parser/TofsenseCascade")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TofsenseCascade>)))
  "Returns md5sum for a message object of type '<TofsenseCascade>"
  "6f5a4318b44b44ec8258733a82bf1f6c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TofsenseCascade)))
  "Returns md5sum for a message object of type 'TofsenseCascade"
  "6f5a4318b44b44ec8258733a82bf1f6c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TofsenseCascade>)))
  "Returns full string definition for message of type '<TofsenseCascade>"
  (cl:format cl:nil "TofsenseFrame0[] nodes~%~%================================================================================~%MSG: nlink_parser/TofsenseFrame0~%uint8 id~%uint32 system_time~%float32 dis~%uint8 dis_status~%uint16 signal_strength~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TofsenseCascade)))
  "Returns full string definition for message of type 'TofsenseCascade"
  (cl:format cl:nil "TofsenseFrame0[] nodes~%~%================================================================================~%MSG: nlink_parser/TofsenseFrame0~%uint8 id~%uint32 system_time~%float32 dis~%uint8 dis_status~%uint16 signal_strength~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TofsenseCascade>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'nodes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TofsenseCascade>))
  "Converts a ROS message object to a list"
  (cl:list 'TofsenseCascade
    (cl:cons ':nodes (nodes msg))
))
