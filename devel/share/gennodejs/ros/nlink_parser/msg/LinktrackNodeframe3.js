// Auto-generated. Do not edit!

// (in-package nlink_parser.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LinktrackNode2 = require('./LinktrackNode2.js');

//-----------------------------------------------------------

class LinktrackNodeframe3 {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.role = null;
      this.id = null;
      this.local_time = null;
      this.system_time = null;
      this.voltage = null;
      this.nodes = null;
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
      if (initObj.hasOwnProperty('nodes')) {
        this.nodes = initObj.nodes
      }
      else {
        this.nodes = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LinktrackNodeframe3
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
    // Serialize message field [nodes]
    // Serialize the length for message field [nodes]
    bufferOffset = _serializer.uint32(obj.nodes.length, buffer, bufferOffset);
    obj.nodes.forEach((val) => {
      bufferOffset = LinktrackNode2.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LinktrackNodeframe3
    let len;
    let data = new LinktrackNodeframe3(null);
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
    // Deserialize message field [nodes]
    // Deserialize array length for message field [nodes]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.nodes = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.nodes[i] = LinktrackNode2.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 14 * object.nodes.length;
    return length + 18;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nlink_parser/LinktrackNodeframe3';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd5fe6bc25d71efe36dc5d4595d69025e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 role
    uint8 id
    uint32 local_time
    uint32 system_time
    float32 voltage
    LinktrackNode2[] nodes
    
    ================================================================================
    MSG: nlink_parser/LinktrackNode2
    uint8 role
    uint8 id
    float32 dis
    float32 fp_rssi
    float32 rx_rssi
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LinktrackNodeframe3(null);
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

    if (msg.nodes !== undefined) {
      resolved.nodes = new Array(msg.nodes.length);
      for (let i = 0; i < resolved.nodes.length; ++i) {
        resolved.nodes[i] = LinktrackNode2.Resolve(msg.nodes[i]);
      }
    }
    else {
      resolved.nodes = []
    }

    return resolved;
    }
};

module.exports = LinktrackNodeframe3;
