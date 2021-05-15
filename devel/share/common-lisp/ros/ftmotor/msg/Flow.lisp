; Auto-generated. Do not edit!


(cl:in-package ftmotor-msg)


;//! \htmlinclude Flow.msg.html

(cl:defclass <Flow> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (vx
    :reader vx
    :initarg :vx
    :type cl:float
    :initform 0.0)
   (vy
    :reader vy
    :initarg :vy
    :type cl:float
    :initform 0.0)
   (pos
    :reader pos
    :initarg :pos
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (theta
    :reader theta
    :initarg :theta
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (hight
    :reader hight
    :initarg :hight
    :type cl:float
    :initform 0.0)
   (valid
    :reader valid
    :initarg :valid
    :type cl:fixnum
    :initform 0)
   (quality
    :reader quality
    :initarg :quality
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Flow (<Flow>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Flow>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Flow)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ftmotor-msg:<Flow> is deprecated: use ftmotor-msg:Flow instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:header-val is deprecated.  Use ftmotor-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'vx-val :lambda-list '(m))
(cl:defmethod vx-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:vx-val is deprecated.  Use ftmotor-msg:vx instead.")
  (vx m))

(cl:ensure-generic-function 'vy-val :lambda-list '(m))
(cl:defmethod vy-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:vy-val is deprecated.  Use ftmotor-msg:vy instead.")
  (vy m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:pos-val is deprecated.  Use ftmotor-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'theta-val :lambda-list '(m))
(cl:defmethod theta-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:theta-val is deprecated.  Use ftmotor-msg:theta instead.")
  (theta m))

(cl:ensure-generic-function 'hight-val :lambda-list '(m))
(cl:defmethod hight-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:hight-val is deprecated.  Use ftmotor-msg:hight instead.")
  (hight m))

(cl:ensure-generic-function 'valid-val :lambda-list '(m))
(cl:defmethod valid-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:valid-val is deprecated.  Use ftmotor-msg:valid instead.")
  (valid m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <Flow>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ftmotor-msg:quality-val is deprecated.  Use ftmotor-msg:quality instead.")
  (quality m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Flow>) ostream)
  "Serializes a message object of type '<Flow>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pos))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'theta))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'hight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'valid)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Flow>) istream)
  "Deserializes a message object of type '<Flow>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy) (roslisp-utils:decode-single-float-bits bits)))
  (cl:setf (cl:slot-value msg 'pos) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'pos)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'theta) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'theta)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'hight) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'valid)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Flow>)))
  "Returns string type for a message object of type '<Flow>"
  "ftmotor/Flow")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Flow)))
  "Returns string type for a message object of type 'Flow"
  "ftmotor/Flow")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Flow>)))
  "Returns md5sum for a message object of type '<Flow>"
  "25d2bfe030c1d5b1bb0b07b36bea3b01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Flow)))
  "Returns md5sum for a message object of type 'Flow"
  "25d2bfe030c1d5b1bb0b07b36bea3b01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Flow>)))
  "Returns full string definition for message of type '<Flow>"
  (cl:format cl:nil "Header header~%float32 vx~%float32 vy~%float32[3] pos~%float32[3] theta~%float32 hight~%uint8 valid~%uint8 quality~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Flow)))
  "Returns full string definition for message of type 'Flow"
  (cl:format cl:nil "Header header~%float32 vx~%float32 vy~%float32[3] pos~%float32[3] theta~%float32 hight~%uint8 valid~%uint8 quality~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Flow>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'theta) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Flow>))
  "Converts a ROS message object to a list"
  (cl:list 'Flow
    (cl:cons ':header (header msg))
    (cl:cons ':vx (vx msg))
    (cl:cons ':vy (vy msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':theta (theta msg))
    (cl:cons ':hight (hight msg))
    (cl:cons ':valid (valid msg))
    (cl:cons ':quality (quality msg))
))
