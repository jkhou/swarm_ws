;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::SwarmPosStamped)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'SwarmPosStamped (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::SWARMPOSSTAMPED")
  (make-package "NLINK_PARSER::SWARMPOSSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude SwarmPosStamped.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nlink_parser::SwarmPosStamped
  :super ros::object
  :slots (_header _poses ))

(defmethod nlink_parser::SwarmPosStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:poses __poses) (let (r) (dotimes (i 4) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _poses __poses)
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
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[4] _poses
    (apply #'+ (send-all _poses :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[4] _poses
     (dolist (elem _poses)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[4] _poses
   (dotimes (i 4)
     (send (elt _poses i) :deserialize buf ptr-) (incf ptr- (send (elt _poses i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get nlink_parser::SwarmPosStamped :md5sum-) "672cc37da9e1e0dee9bea324fba5efb7")
(setf (get nlink_parser::SwarmPosStamped :datatype-) "nlink_parser/SwarmPosStamped")
(setf (get nlink_parser::SwarmPosStamped :definition-)
      "std_msgs/Header header
geometry_msgs/Point[4] poses
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



(provide :nlink_parser/SwarmPosStamped "672cc37da9e1e0dee9bea324fba5efb7")


