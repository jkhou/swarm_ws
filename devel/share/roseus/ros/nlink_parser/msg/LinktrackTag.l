;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackTag)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackTag (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKTAG")
  (make-package "NLINK_PARSER::LINKTRACKTAG"))

(in-package "ROS")
;;//! \htmlinclude LinktrackTag.msg.html


(defclass nlink_parser::LinktrackTag
  :super ros::object
  :slots (_role _id _pos_3d _dis_arr ))

(defmethod nlink_parser::LinktrackTag
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:pos_3d __pos_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:dis_arr __dis_arr) (make-array 8 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _pos_3d __pos_3d)
   (setq _dis_arr __dis_arr)
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:pos_3d
   (&optional __pos_3d)
   (if __pos_3d (setq _pos_3d __pos_3d)) _pos_3d)
  (:dis_arr
   (&optional __dis_arr)
   (if __dis_arr (setq _dis_arr __dis_arr)) _dis_arr)
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; float32[3] _pos_3d
    (* 4    3)
    ;; float32[8] _dis_arr
    (* 4    8)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; float32[3] _pos_3d
     (dotimes (i 3)
       (sys::poke (elt _pos_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[8] _dis_arr
     (dotimes (i 8)
       (sys::poke (elt _dis_arr i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32[3] _pos_3d
   (dotimes (i (length _pos_3d))
     (setf (elt _pos_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[8] _dis_arr
   (dotimes (i (length _dis_arr))
     (setf (elt _dis_arr i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackTag :md5sum-) "4a4bf3020fbef59e2422a9233d276302")
(setf (get nlink_parser::LinktrackTag :datatype-) "nlink_parser/LinktrackTag")
(setf (get nlink_parser::LinktrackTag :definition-)
      "uint8 role
uint8 id
float32[3] pos_3d
float32[8] dis_arr

")



(provide :nlink_parser/LinktrackTag "4a4bf3020fbef59e2422a9233d276302")


