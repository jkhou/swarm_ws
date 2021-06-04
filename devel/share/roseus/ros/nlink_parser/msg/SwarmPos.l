;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::SwarmPos)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'SwarmPos (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::SWARMPOS")
  (make-package "NLINK_PARSER::SWARMPOS"))

(in-package "ROS")
;;//! \htmlinclude SwarmPos.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nlink_parser::SwarmPos
  :super ros::object
  :slots (_header _swarm_pos ))

(defmethod nlink_parser::SwarmPos
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:swarm_pos __swarm_pos) (let (r) (dotimes (i 16) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _swarm_pos __swarm_pos)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:swarm_pos
   (&rest __swarm_pos)
   (if (keywordp (car __swarm_pos))
       (send* _swarm_pos __swarm_pos)
     (progn
       (if __swarm_pos (setq _swarm_pos (car __swarm_pos)))
       _swarm_pos)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[16] _swarm_pos
    (apply #'+ (send-all _swarm_pos :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[16] _swarm_pos
     (dolist (elem _swarm_pos)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[16] _swarm_pos
   (dotimes (i 16)
     (send (elt _swarm_pos i) :deserialize buf ptr-) (incf ptr- (send (elt _swarm_pos i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get nlink_parser::SwarmPos :md5sum-) "1c5deeae29fc99ca2d59a905d86e689d")
(setf (get nlink_parser::SwarmPos :datatype-) "nlink_parser/SwarmPos")
(setf (get nlink_parser::SwarmPos :definition-)
      "std_msgs/Header header
geometry_msgs/Point[16] swarm_pos
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



(provide :nlink_parser/SwarmPos "1c5deeae29fc99ca2d59a905d86e689d")


