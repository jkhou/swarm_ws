;; Auto-generated. Do not edit!


(when (boundp 'nlink_parser::LinktrackTagframe0)
  (if (not (find-package "NLINK_PARSER"))
    (make-package "NLINK_PARSER"))
  (shadow 'LinktrackTagframe0 (find-package "NLINK_PARSER")))
(unless (find-package "NLINK_PARSER::LINKTRACKTAGFRAME0")
  (make-package "NLINK_PARSER::LINKTRACKTAGFRAME0"))

(in-package "ROS")
;;//! \htmlinclude LinktrackTagframe0.msg.html


(defclass nlink_parser::LinktrackTagframe0
  :super ros::object
  :slots (_role _id _local_time _system_time _voltage _pos_3d _eop_3d _vel_3d _dis_arr _angle_3d _quaternion _imu_gyro_3d _imu_acc_3d ))

(defmethod nlink_parser::LinktrackTagframe0
  (:init
   (&key
    ((:role __role) 0)
    ((:id __id) 0)
    ((:local_time __local_time) 0)
    ((:system_time __system_time) 0)
    ((:voltage __voltage) 0.0)
    ((:pos_3d __pos_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:eop_3d __eop_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:vel_3d __vel_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:dis_arr __dis_arr) (make-array 8 :initial-element 0.0 :element-type :float))
    ((:angle_3d __angle_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:quaternion __quaternion) (make-array 4 :initial-element 0.0 :element-type :float))
    ((:imu_gyro_3d __imu_gyro_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:imu_acc_3d __imu_acc_3d) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _role (round __role))
   (setq _id (round __id))
   (setq _local_time (round __local_time))
   (setq _system_time (round __system_time))
   (setq _voltage (float __voltage))
   (setq _pos_3d __pos_3d)
   (setq _eop_3d __eop_3d)
   (setq _vel_3d __vel_3d)
   (setq _dis_arr __dis_arr)
   (setq _angle_3d __angle_3d)
   (setq _quaternion __quaternion)
   (setq _imu_gyro_3d __imu_gyro_3d)
   (setq _imu_acc_3d __imu_acc_3d)
   self)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:local_time
   (&optional __local_time)
   (if __local_time (setq _local_time __local_time)) _local_time)
  (:system_time
   (&optional __system_time)
   (if __system_time (setq _system_time __system_time)) _system_time)
  (:voltage
   (&optional __voltage)
   (if __voltage (setq _voltage __voltage)) _voltage)
  (:pos_3d
   (&optional __pos_3d)
   (if __pos_3d (setq _pos_3d __pos_3d)) _pos_3d)
  (:eop_3d
   (&optional __eop_3d)
   (if __eop_3d (setq _eop_3d __eop_3d)) _eop_3d)
  (:vel_3d
   (&optional __vel_3d)
   (if __vel_3d (setq _vel_3d __vel_3d)) _vel_3d)
  (:dis_arr
   (&optional __dis_arr)
   (if __dis_arr (setq _dis_arr __dis_arr)) _dis_arr)
  (:angle_3d
   (&optional __angle_3d)
   (if __angle_3d (setq _angle_3d __angle_3d)) _angle_3d)
  (:quaternion
   (&optional __quaternion)
   (if __quaternion (setq _quaternion __quaternion)) _quaternion)
  (:imu_gyro_3d
   (&optional __imu_gyro_3d)
   (if __imu_gyro_3d (setq _imu_gyro_3d __imu_gyro_3d)) _imu_gyro_3d)
  (:imu_acc_3d
   (&optional __imu_acc_3d)
   (if __imu_acc_3d (setq _imu_acc_3d __imu_acc_3d)) _imu_acc_3d)
  (:serialization-length
   ()
   (+
    ;; uint8 _role
    1
    ;; uint8 _id
    1
    ;; uint32 _local_time
    4
    ;; uint32 _system_time
    4
    ;; float32 _voltage
    4
    ;; float32[3] _pos_3d
    (* 4    3)
    ;; float32[3] _eop_3d
    (* 4    3)
    ;; float32[3] _vel_3d
    (* 4    3)
    ;; float32[8] _dis_arr
    (* 4    8)
    ;; float32[3] _angle_3d
    (* 4    3)
    ;; float32[4] _quaternion
    (* 4    4)
    ;; float32[3] _imu_gyro_3d
    (* 4    3)
    ;; float32[3] _imu_acc_3d
    (* 4    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _role
       (write-byte _role s)
     ;; uint8 _id
       (write-byte _id s)
     ;; uint32 _local_time
       (write-long _local_time s)
     ;; uint32 _system_time
       (write-long _system_time s)
     ;; float32 _voltage
       (sys::poke _voltage (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32[3] _pos_3d
     (dotimes (i 3)
       (sys::poke (elt _pos_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _eop_3d
     (dotimes (i 3)
       (sys::poke (elt _eop_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _vel_3d
     (dotimes (i 3)
       (sys::poke (elt _vel_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[8] _dis_arr
     (dotimes (i 8)
       (sys::poke (elt _dis_arr i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _angle_3d
     (dotimes (i 3)
       (sys::poke (elt _angle_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[4] _quaternion
     (dotimes (i 4)
       (sys::poke (elt _quaternion i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _imu_gyro_3d
     (dotimes (i 3)
       (sys::poke (elt _imu_gyro_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _imu_acc_3d
     (dotimes (i 3)
       (sys::poke (elt _imu_acc_3d i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _role
     (setq _role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint32 _local_time
     (setq _local_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _system_time
     (setq _system_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _voltage
     (setq _voltage (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32[3] _pos_3d
   (dotimes (i (length _pos_3d))
     (setf (elt _pos_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _eop_3d
   (dotimes (i (length _eop_3d))
     (setf (elt _eop_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _vel_3d
   (dotimes (i (length _vel_3d))
     (setf (elt _vel_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[8] _dis_arr
   (dotimes (i (length _dis_arr))
     (setf (elt _dis_arr i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _angle_3d
   (dotimes (i (length _angle_3d))
     (setf (elt _angle_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[4] _quaternion
   (dotimes (i (length _quaternion))
     (setf (elt _quaternion i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _imu_gyro_3d
   (dotimes (i (length _imu_gyro_3d))
     (setf (elt _imu_gyro_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _imu_acc_3d
   (dotimes (i (length _imu_acc_3d))
     (setf (elt _imu_acc_3d i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get nlink_parser::LinktrackTagframe0 :md5sum-) "20cc09884b3e1aa830a1d8a71796a857")
(setf (get nlink_parser::LinktrackTagframe0 :datatype-) "nlink_parser/LinktrackTagframe0")
(setf (get nlink_parser::LinktrackTagframe0 :definition-)
      "uint8 role
uint8 id
uint32 local_time
uint32 system_time
float32 voltage
float32[3] pos_3d
float32[3] eop_3d
float32[3] vel_3d
float32[8] dis_arr
float32[3] angle_3d
float32[4] quaternion
float32[3] imu_gyro_3d
float32[3] imu_acc_3d


")



(provide :nlink_parser/LinktrackTagframe0 "20cc09884b3e1aa830a1d8a71796a857")


