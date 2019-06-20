;; Auto-generated. Do not edit!


(when (boundp 'camera_show::where)
  (if (not (find-package "CAMERA_SHOW"))
    (make-package "CAMERA_SHOW"))
  (shadow 'where (find-package "CAMERA_SHOW")))
(unless (find-package "CAMERA_SHOW::WHERE")
  (make-package "CAMERA_SHOW::WHERE"))

(in-package "ROS")
;;//! \htmlinclude where.msg.html


(defclass camera_show::where
  :super ros::object
  :slots (_data ))

(defmethod camera_show::where
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

(setf (get camera_show::where :md5sum-) "da5909fbe378aeaf85e547e830cc1bb7")
(setf (get camera_show::where :datatype-) "camera_show/where")
(setf (get camera_show::where :definition-)
      "int32 data

")



(provide :camera_show/where "da5909fbe378aeaf85e547e830cc1bb7")


