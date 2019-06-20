;; Auto-generated. Do not edit!


(when (boundp 'camera_on::where)
  (if (not (find-package "CAMERA_ON"))
    (make-package "CAMERA_ON"))
  (shadow 'where (find-package "CAMERA_ON")))
(unless (find-package "CAMERA_ON::WHERE")
  (make-package "CAMERA_ON::WHERE"))

(in-package "ROS")
;;//! \htmlinclude where.msg.html


(defclass camera_on::where
  :super ros::object
  :slots (_data ))

(defmethod camera_on::where
  (:init
   (&key
    ((:data __data) 0)
    )
   (send-super :init)
   (setq _data (round __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; int32 _data
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _data
       (write-long _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _data
     (setq _data (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get camera_on::where :md5sum-) "da5909fbe378aeaf85e547e830cc1bb7")
(setf (get camera_on::where :datatype-) "camera_on/where")
(setf (get camera_on::where :definition-)
      "int32 data

")



(provide :camera_on/where "da5909fbe378aeaf85e547e830cc1bb7")


