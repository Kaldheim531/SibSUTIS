import React, { useState } from 'react';
import ReactFlow, {
  MiniMap,
  Controls,
  Background,
  addEdge,
  useNodesState,
  useEdgesState,
} from 'reactflow';
import 'reactflow/dist/style.css';

// Исходные данные
const initialNodes = [
  {
    id: '1',
    type: 'input',
    data: { label: 'Build', startTime: null, endTime: null },
    position: { x: 250, y: 0 },
    status: 'Pending',
  },
  {
    id: '2',
    data: { label: 'Test', startTime: null, endTime: null },
    position: { x: 100, y: 150 },
    status: 'Pending',
  },
  {
    id: '3',
    data: { label: 'Deploy', startTime: null, endTime: null },
    position: { x: 400, y: 150 },
    status: 'Pending',
  },
];

const initialEdges = [
  { id: 'e1-2', source: '1', target: '2', animated: true },
  { id: 'e1-3', source: '1', target: '3', animated: true },
];

const statusColors = {
  Pending: '#f0ad4e', // Оранжевый
  Running: '#5bc0de', // Голубой
  Completed: '#5cb85c', // Зеленый
  Failed: '#d9534f', // Красный
};

const Pipeline = () => {
  const [nodes, setNodes, onNodesChange] = useNodesState(initialNodes);
  const [edges, setEdges, onEdgesChange] = useEdgesState(initialEdges);
  const [logs, setLogs] = useState([]);
  const [newTaskName, setNewTaskName] = useState('');
  const [taskDetails, setTaskDetails] = useState(null);

  // Обновление статуса задачи и времени
  const updateNodeStatus = (nodeId, status) => {
    setNodes((nds) =>
      nds.map((node) => {
        if (node.id === nodeId) {
          const currentTime = new Date().toLocaleTimeString();
          return {
            ...node,
            status,
            style: { background: statusColors[status], color: '#fff' },
            data: {
              ...node.data,
              startTime: status === 'Running' ? currentTime : node.data.startTime,
              endTime: status === 'Completed' ? currentTime : node.data.endTime,
            },
          };
        }
        return node;
      })
    );
    setLogs((prevLogs) => [...prevLogs, `Task ${nodeId} status updated to ${status}`]);
  };

  // Запуск пайплайна
  const runPipeline = () => {
    let delay = 0;
    nodes.forEach((node) => {
      setTimeout(() => updateNodeStatus(node.id, 'Running'), delay);
      delay += 2000;
      setTimeout(() => updateNodeStatus(node.id, 'Completed'), delay);
      delay += 2000;
    });
  };

  // Остановка всех задач
  const stopPipeline = () => {
    setNodes((nds) =>
      nds.map((node) => ({
        ...node,
        status: 'Failed',
        style: { background: statusColors['Failed'], color: '#fff' },
      }))
    );
    setLogs((prevLogs) => [...prevLogs, 'Pipeline stopped manually']);
  };

  // Перезапуск всех задач
  const restartPipeline = () => {
    setNodes((nds) =>
      nds.map((node) => ({
        ...node,
        status: 'Pending',
        style: { background: statusColors['Pending'], color: '#fff' },
        data: { ...node.data, startTime: null, endTime: null },
      }))
    );
    runPipeline();
  };

  // Добавление новой задачи
  const addNode = (label) => {
    if (!label) return;
    const newNodeId = (nodes.length + 1).toString();
    const newNode = {
      id: newNodeId,
      data: { label, startTime: null, endTime: null },
      position: { x: Math.random() * 600, y: Math.random() * 400 },
      status: 'Pending',
      style: { background: statusColors['Pending'], color: '#fff' },
    };
    const lastNodeId = nodes[nodes.length - 1].id;
    const newEdge = {
      id: `e${lastNodeId}-${newNodeId}`,
      source: lastNodeId,
      target: newNodeId,
      animated: true,
    };
    setNodes((nds) => [...nds, newNode]);
    setEdges((eds) => [...eds, newEdge]);
    setLogs((prevLogs) => [...prevLogs, `Added new task: ${label}`]);
    setNewTaskName('');
  };

  // Обработка клика на узле
  const onNodeClick = (event, node) => {
    setTaskDetails(node);
  };

  return (
    <div style={{ backgroundColor: '#2a2f23', minHeight: '100vh', padding: '20px', color: '#c3e88d' }}>
      <h2 style={{ textAlign: 'center', color: '#9ccc65' }}>CI/CD Pipeline</h2>

      <div style={{ textAlign: 'center', marginBottom: '20px' }}>
        <button onClick={runPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#5cb85c', color: '#fff' }}>
          Run
        </button>
        <button onClick={stopPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#d9534f', color: '#fff' }}>
          Stop
        </button>
        <button onClick={restartPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#5bc0de', color: '#fff' }}>
          Restart
        </button>
      </div>

      <div style={{ textAlign: 'center', marginBottom: '20px' }}>
        <input
          type="text"
          placeholder="Task Name"
          value={newTaskName}
          onChange={(e) => setNewTaskName(e.target.value)}
          style={{
            padding: '5px',
            marginRight: '10px',
            border: '1px solid #9ccc65',
            backgroundColor: '#394a34',
            color: '#c3e88d',
          }}
        />
        <button
          onClick={() => addNode(newTaskName)}
          style={{
            padding: '5px 10px',
            backgroundColor: '#9ccc65',
            color: '#2a2f23',
            border: 'none',
            borderRadius: '5px',
            cursor: 'pointer',
          }}
        >
          Add Task
        </button>
      </div>

      <div style={{ height: '400px', width: '800px', border: '1px solid #9ccc65', margin: 'auto' }}>
        <ReactFlow
          nodes={nodes}
          edges={edges}
          onNodesChange={onNodesChange}
          onEdgesChange={onEdgesChange}
          onNodeClick={onNodeClick}
          fitView
        >
          <MiniMap />
          <Controls />
          <Background color="#555" gap={16} />
        </ReactFlow>
      </div>

      {taskDetails && (
        <div style={{ padding: '20px', margin: '20px auto', border: '1px solid #9ccc65', backgroundColor: '#394a34', width: '800px' }}>
          <h4>Task Details</h4>
          <p><strong>Name:</strong> {taskDetails.data.label}</p>
          <p><strong>Status:</strong> {taskDetails.status}</p>
          <p><strong>Start Time:</strong> {taskDetails.data.startTime || 'N/A'}</p>
          <p><strong>End Time:</strong> {taskDetails.data.endTime || 'N/A'}</p>
        </div>
      )}

      <div style={{ padding: '20px', margin: '20px auto', border: '1px solid #9ccc65', backgroundColor: '#394a34', width: '800px' }}>
        <h4>Logs</h4>
        <div style={{ maxHeight: '150px', overflowY: 'auto' }}>
          {logs.map((log, index) => (
            <p key={index} style={{ margin: '5px 0' }}>
              {log}
            </p>
          ))}
        </div>
      </div>
    </div>
  );
};

export default Pipeline;
