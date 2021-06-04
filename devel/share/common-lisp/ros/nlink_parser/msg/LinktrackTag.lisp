; Auto-generated. Do not edit!


(cl:in-package nlink_parser-msg)


;//! \htmlinclude LinktrackTag.msg.html

(cl:defclass <LinktrackTag> (roslisp-msg-protocol:ros-message)
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
   (pos_3d
    :reader pos_3d
    :initarg :pos_3d
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (dis_arr
    :reader dis_arr
    :initarg :dis_arr
    :type (cl:vector cl:float)
   :initform (cl:make-array 8 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass LinktrackTag (<LinktrackTag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LinktrackTag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LinktrackTag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nlink_parser-msg:<LinktrackTag> is deprecated: use nlink_parser-msg:LinktrackTag instead.")))

(cl:ensure-generic-function 'role-val :lambda-list '(m))
(cl:defmethod role-val ((m <LinktrackTag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:role-val is deprecated.  Use nlink_parser-msg:role instead.")
  (role m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LinktrackTag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:id-val is deprecated.  Use nlink_parser-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'pos_3d-val :lambda-list '(m))
(cl:defmethod pos_3d-val ((m <LinktrackTag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:pos_3d-val is deprecated.  Use nlink_parser-msg:pos_3d instead.")
  (pos_3d m))

(cl:ensure-generic-function 'dis_arr-val :lambda-list '(m))
(cl:defmethod dis_arr-val ((m <LinktrackTag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nlink_parser-msg:dis_arr-val is deprecated.  Use nlink_parser-msg:dis_arr instead.")
  (dis_arr m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LinktrackTag>) ostream)
  "Serializes a message object of type '<LinktrackTag>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'pos_3d))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'dis_arr))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LinktrackTag>) istream)
  "Deserializes a message object of type '<LinktrackTag>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'role)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'pos_3d) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'pos_3d)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'dis_arr) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'dis_arr)))
    (cl:dotimes (i 8)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LinktrackTag>)))
  "Returns string type for a message object of type '<LinktrackTag>"
  "nlink_parser/LinktrackTag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LinktrackTag)))
  "Returns string type for a message object of type 'LinktrackTag"
  "nlink_parser/LinktrackTag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LinktrackTag>)))
  "Returns md5sum for a message object of type '<LinktrackTag>"
  "4a4bf3020fbef59e2422a9233d276302")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LinktrackTag)))
  "Returns md5sum for a message object of type 'LinktrackTag"
  "4a4bf3020fbef59e2422a9233d276302")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LinktrackTag>)))
  "Returns full string definition for message of type '<LinktrackTag>"
  (cl:format cl:nil "uint8 role~%uint8 id~%float32[3] pos_3d~%float32[8] dis_arr~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LinktrackTag)))
  "Returns full string definition for message of type 'LinktrackTag"
  (cl:format cl:nil "uint8 role~%uint8 id~%float32[3] pos_3d~%float32[8] dis_arr~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LinktrackTag>))
  (cl:+ 0
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pos_3d) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'dis_arr) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LinktrackTag>))
  "Converts a ROS message object to a list"
  (cl:list 'LinktrackTag
    (cl:cons ':role (role msg))
    (cl:cons ':id (id msg))
    (cl:cons ':pos_3d (pos_3d msg))
    (cl:cons ':dis_arr (dis_arr msg))
))
