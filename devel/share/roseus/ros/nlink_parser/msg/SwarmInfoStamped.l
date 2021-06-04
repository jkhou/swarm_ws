;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::SwarmInfoStamped)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'SwarmInfoStamped (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::SWARMINFOSTAMPED")
  (make-package "NLINK_PARSER::SWARMINFOSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude SwarmInfoStamped.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nlink_parser::SwarmInfoStamped
  :super ros::object
  :slots (_header _poses _vel ))

(defmethod nlink_parser::SwarmInfoStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:poses __poses) (let (r) (dotimes (i 16) (push (instance geometry_msgs::Point :init) r)) r))
    ((:vel __vel) (let (r) (dotimes (i 4) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _poses __poses)
   (setq _vel __vel)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:poses
   (&rest __poses)
   (if (keywordp (car __poses))
       (send* _poses __poses)
     (progn
       (if __poses (setq _poses (car __poses)))
       _poses)))
  (:vel
   (&rest __vel)
   (if (keywordp (car __vel))
       (send* _vel __vel)
     (progn
       (if __vel (setq _vel (car __vel)))
       _vel)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[16] _poses
    (apply #'+ (send-all _poses :serialization-length))
    ;; geometry_msgs/Point[4] _vel
    (apply #'+ (send-all _vel :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[16] _poses
     (dolist (elem _poses)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Point[4] _vel
     (dolist (elem _vel)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[16] _poses
   (dotimes (i 16)
     (send (elt _poses i) :deserialize buf ptr-) (incf ptr- (send (elt _poses i) :serialization-length))
     )
   ;; geometry_msgs/Point[4] _vel
   (dotimes (i 4)
     (send (elt _vel i) :deserialize buf ptr-) (incf ptr- (send (elt _vel i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get nlink_parser::SwarmInfoStamped :md5sum-) "13aee0f85f95ab4c91a15c97f46b7cc3")
(setf (get nlink_parser::SwarmInfoStamped :datatype-) "nlink_parser/SwarmInfoStamped")
(setf (get nlink_parser::SwarmInfoStamped :definition-)
      "std_msgs/Header header
geometry_msgs/Point[16] poses
geometry_msgs/Point[4] vel
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :nlink_parser/SwarmInfoStamped "13aee0f85f95ab4c91a15c97f46b7cc3")


