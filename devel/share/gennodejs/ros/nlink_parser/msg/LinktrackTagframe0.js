// Auto-generated. Do not edit!

// (in-package nlink_parser.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class LinktrackTagframe0 {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.role = null;
      this.id = null;
      this.local_time = null;
      this.system_time = null;
      this.voltage = null;
      this.pos_3d = null;
      this.eop_3d = null;
      this.vel_3d = null;
      this.dis_arr = null;
      this.angle_3d = null;
      this.quaternion = null;
      this.imu_gyro_3d = null;
      this.imu_acc_3d = null;
    }
    else {
      if (initObj.hasOwnProperty('role')) {
        this.role = initObj.role
      }
      else {
        this.role = 0;
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('local_time')) {
        this.local_time = initObj.local_time
      }
      else {
        this.local_time = 0;
      }
      if (initObj.hasOwnProperty('system_time')) {
        this.system_time = initObj.system_time
      }
      else {
        this.system_time = 0;
      }
      if (initObj.hasOwnProperty('voltage')) {
        this.voltage = initObj.voltage
      }
      else {
        this.voltage = 0.0;
      }
      if (initObj.hasOwnProperty('pos_3d')) {
        this.pos_3d = initObj.pos_3d
      }
      else {
        this.pos_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('eop_3d')) {
        this.eop_3d = initObj.eop_3d
      }
      else {
        this.eop_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('vel_3d')) {
        this.vel_3d = initObj.vel_3d
      }
      else {
        this.vel_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('dis_arr')) {
        this.dis_arr = initObj.dis_arr
      }
      else {
        this.dis_arr = new Array(8).fill(0);
      }
      if (initObj.hasOwnProperty('angle_3d')) {
        this.angle_3d = initObj.angle_3d
      }
      else {
        this.angle_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('quaternion')) {
        this.quaternion = initObj.quaternion
      }
      else {
        this.quaternion = new Array(4).fill(0);
      }
      if (initObj.hasOwnProperty('imu_gyro_3d')) {
        this.imu_gyro_3d = initObj.imu_gyro_3d
      }
      else {
        this.imu_gyro_3d = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('imu_acc_3d')) {
        this.imu_acc_3d = initObj.imu_acc_3d
      }
      else {
        this.imu_acc_3d = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LinktrackTagframe0
    // Serialize message field [role]
    bufferOffset = _serializer.uint8(obj.role, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.uint8(obj.id, buffer, bufferOffset);
    // Serialize message field [local_time]
    bufferOffset = _serializer.uint32(obj.local_time, buffer, bufferOffset);
    // Serialize message field [system_time]
    bufferOffset = _serializer.uint32(obj.system_time, buffer, bufferOffset);
    // Serialize message field [voltage]
    bufferOffset = _serializer.float32(obj.voltage, buffer, bufferOffset);
    // Check that the constant length array field [pos_3d] has the right length
    if (obj.pos_3d.length !== 3) {
      throw new Error('Unable to serialize array field pos_3d - length must be 3')
    }
    // Serialize message field [pos_3d]
    bufferOffset = _arraySerializer.float32(obj.pos_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [eop_3d] has the right length
    if (obj.eop_3d.length !== 3) {
      throw new Error('Unable to serialize array field eop_3d - length must be 3')
    }
    // Serialize message field [eop_3d]
    bufferOffset = _arraySerializer.float32(obj.eop_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [vel_3d] has the right length
    if (obj.vel_3d.length !== 3) {
      throw new Error('Unable to serialize array field vel_3d - length must be 3')
    }
    // Serialize message field [vel_3d]
    bufferOffset = _arraySerializer.float32(obj.vel_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [dis_arr] has the right length
    if (obj.dis_arr.length !== 8) {
      throw new Error('Unable to serialize array field dis_arr - length must be 8')
    }
    // Serialize message field [dis_arr]
    bufferOffset = _arraySerializer.float32(obj.dis_arr, buffer, bufferOffset, 8);
    // Check that the constant length array field [angle_3d] has the right length
    if (obj.angle_3d.length !== 3) {
      throw new Error('Unable to serialize array field angle_3d - length must be 3')
    }
    // Serialize message field [angle_3d]
    bufferOffset = _arraySerializer.float32(obj.angle_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [quaternion] has the right length
    if (obj.quaternion.length !== 4) {
      throw new Error('Unable to serialize array field quaternion - length must be 4')
    }
    // Serialize message field [quaternion]
    bufferOffset = _arraySerializer.float32(obj.quaternion, buffer, bufferOffset, 4);
    // Check that the constant length array field [imu_gyro_3d] has the right length
    if (obj.imu_gyro_3d.length !== 3) {
      throw new Error('Unable to serialize array field imu_gyro_3d - length must be 3')
    }
    // Serialize message field [imu_gyro_3d]
    bufferOffset = _arraySerializer.float32(obj.imu_gyro_3d, buffer, bufferOffset, 3);
    // Check that the constant length array field [imu_acc_3d] has the right length
    if (obj.imu_acc_3d.length !== 3) {
      throw new Error('Unable to serialize array field imu_acc_3d - length must be 3')
    }
    // Serialize message field [imu_acc_3d]
    bufferOffset = _arraySerializer.float32(obj.imu_acc_3d, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LinktrackTagframe0
    let len;
    let data = new LinktrackTagframe0(null);
    // Deserialize message field [role]
    data.role = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [local_time]
    data.local_time = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [system_time]
    data.system_time = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [voltage]
    data.voltage = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pos_3d]
    data.pos_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [eop_3d]
    data.eop_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [vel_3d]
    data.vel_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [dis_arr]
    data.dis_arr = _arrayDeserializer.float32(buffer, bufferOffset, 8)
    // Deserialize message field [angle_3d]
    data.angle_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [quaternion]
    data.quaternion = _arrayDeserializer.float32(buffer, bufferOffset, 4)
    // Deserialize message field [imu_gyro_3d]
    data.imu_gyro_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [imu_acc_3d]
    data.imu_acc_3d = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 134;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nlink_parser/LinktrackTagframe0';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '20cc09884b3e1aa830a1d8a71796a857';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 role
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
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LinktrackTagframe0(null);
    if (msg.role !== undefined) {
      resolved.role = msg.role;
    }
    else {
      resolved.role = 0
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.local_time !== undefined) {
      resolved.local_time = msg.local_time;
    }
    else {
      resolved.local_time = 0
    }

    if (msg.system_time !== undefined) {
      resolved.system_time = msg.system_time;
    }
    else {
      resolved.system_time = 0
    }

    if (msg.voltage !== undefined) {
      resolved.voltage = msg.voltage;
    }
    else {
      resolved.voltage = 0.0
    }

    if (msg.pos_3d !== undefined) {
      resolved.pos_3d = msg.pos_3d;
    }
    else {
      resolved.pos_3d = new Array(3).fill(0)
    }

    if (msg.eop_3d !== undefined) {
      resolved.eop_3d = msg.eop_3d;
    }
    else {
      resolved.eop_3d = new Array(3).fill(0)
    }

    if (msg.vel_3d !== undefined) {
      resolved.vel_3d = msg.vel_3d;
    }
    else {
      resolved.vel_3d = new Array(3).fill(0)
    }

    if (msg.dis_arr !== undefined) {
      resolved.dis_arr = msg.dis_arr;
    }
    else {
      resolved.dis_arr = new Array(8).fill(0)
    }

    if (msg.angle_3d !== undefined) {
      resolved.angle_3d = msg.angle_3d;
    }
    else {
      resolved.angle_3d = new Array(3).fill(0)
    }

    if (msg.quaternion !== undefined) {
      resolved.quaternion = msg.quaternion;
    }
    else {
      resolved.quaternion = new Array(4).fill(0)
    }

    if (msg.imu_gyro_3d !== undefined) {
      resolved.imu_gyro_3d = msg.imu_gyro_3d;
    }
    else {
      resolved.imu_gyro_3d = new Array(3).fill(0)
    }

    if (msg.imu_acc_3d !== undefined) {
      resolved.imu_acc_3d = msg.imu_acc_3d;
    }
    else {
      resolved.imu_acc_3d = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = LinktrackTagframe0;
