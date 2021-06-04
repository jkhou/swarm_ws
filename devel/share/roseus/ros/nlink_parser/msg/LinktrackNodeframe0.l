;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackNodeframe0)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackNodeframe0 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKNODEFRAME0")
  (make-package "NLINK_PARSER::LINKTRACKNODEFRAME0"))

(in-package "ROS")
;;//! \htmlinclude LinktrackNodeframe0.msg.html


(defclass nlink_parser::LinktrackNodeframe0
  :super ros::object
  :slots (_role _id _nodes ))

(defmethod nlink_parser::LinktrackNodeframe0
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:nodes __nodes) (let (r) (dotimes (i 0) (push (instance nlink_parser::LinktrackNode0 :init) r)) r))
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _nodes __nodes)
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:nodes
   (&rest __nodes)
   (if (keywordp (car __nodes))
       (send* _nodes __nodes)
     (progn
       (if __nodes (setq _nodes (car __nodes)))
       _nodes)))
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; nlink_parser/LinktrackNode0[] _nodes
    (apply #'+ (send-all _nodes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; nlink_parser/LinktrackNode0[] _nodes
     (write-long (length _nodes) s)
     (dolist (elem _nodes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; nlink_parser/LinktrackNode0[] _nodes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _nodes (let (r) (dotimes (i n) (push (instance nlink_parser::LinktrackNode0 :init) r)) r))
     (dolist (elem- _nodes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackNodeframe0 :md5sum-) "99d2eee732fdf2fb898d64e9172d0e66")
(setf (get nlink_parser::LinktrackNodeframe0 :datatype-) "nlink_parser/LinktrackNodeframe0")
(setf (get nlink_parser::LinktrackNodeframe0 :definition-)
      "uint8 role
uint8 id
LinktrackNode0[] nodes

================================================================================
MSG: nlink_parser/LinktrackNode0
uint8 role
uint8 id
uint8[] data

")



(provide :nlink_parser/LinktrackNodeframe0 "99d2eee732fdf2fb898d64e9172d0e66")


