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
  { id: '1', type: 'input', data: { label: 'Build' }, position: { x: 250, y: 0 }, status: 'Pending' },
  { id: '2', data: { label: 'Test' }, position: { x: 100, y: 150 }, status: 'Pending' },
  { id: '3', data: { label: 'Deploy' }, position: { x: 400, y: 150 }, status: 'Pending' },
];

const initialEdges = [
  { id: 'e1-2', source: '1', target: '2', animated: true },
  { id: 'e1-3', source: '1', target: '3', animated: true },
];

const statusColors = {
  Pending: '#f0ad4e',    // Оранжевый
  Running: '#5bc0de',    // Голубой
  Completed: '#5cb85c',  // Зеленый
  Failed: '#d9534f',     // Красный
};

const Pipeline = () => {
  const [nodes, setNodes, onNodesChange] = useNodesState(initialNodes);
  const [edges, setEdges, onEdgesChange] = useEdgesState(initialEdges);
  const [logs, setLogs] = useState([]);
  const [newTaskName, setNewTaskName] = useState('');
  const [taskDetails, setTaskDetails] = useState(null);
  const [filteredLogs, setFilteredLogs] = useState(logs);

  const logTypes = ['info', 'warning', 'error'];

  // Обновление статуса задачи
  const updateNodeStatus = (nodeId, status) => {
    setNodes((nds) =>
      nds.map((node) => {
        if (node.id === nodeId) {
          return {
            ...node, // сохраняем старые свойства
            status,  // обновляем статус
            style: { background: statusColors[status], color: '#fff' }, // обновляем стиль
          };
        }
        return node; // если это не тот узел, возвращаем его без изменений
      })
    );
    setLogs((prevLogs) => [...prevLogs, `Task ${nodeId} status updated to ${status}`]);
  };

  // Запуск пайплайна
  const runPipeline = () => {
    // Обновляем статус задачи Build
    updateNodeStatus('1', 'Running');
    
    // После 2 секунд обновляем статус Build на Completed и начинаем Test
    setTimeout(() => {
      updateNodeStatus('1', 'Completed');
      updateNodeStatus('2', 'Running');
    }, 2000);
    
    // После 4 секунд обновляем статус Test на Completed и начинаем Deploy
    setTimeout(() => {
      updateNodeStatus('2', 'Completed');
      updateNodeStatus('3', 'Running');
    }, 4000);
    
    // После 6 секунд обновляем статус Deploy на Completed
    setTimeout(() => {
      updateNodeStatus('3', 'Completed');
    }, 6000);
  };
  

  // Функция остановки всех задач
  const stopPipeline = () => {
    setNodes((nds) =>
      nds.map((node) => ({
        ...node,
        status: 'Failed',
        style: { background: statusColors['Failed'], color: '#fff' },
      }))
    );
    setLogs((prevLogs) => [...prevLogs, { type: 'warning', message: 'Pipeline stopped manually' }]);
  };

  const restartPipeline = () => {
    setNodes((nds) =>
      nds.map((node) => ({
        ...node,
        status: 'Pending',
        style: { background: statusColors['Pending'], color: '#fff' },
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
    data: { label },
    position: { x: Math.random() * 600, y: Math.random() * 400 },
    status: 'Pending',  // Статус Pending при добавлении
    style: { background: statusColors['Pending'], color: '#fff' },  // Цвет по статусу
  };

  // Обновляем состояние узлов
  setNodes((nds) => [...nds, newNode]);
  setLogs((prevLogs) => [...prevLogs, `Added new task: ${label}`]);
  setNewTaskName(''); // Очистить поле ввода
};


  const filterLogs = (type) => {
    setFilteredLogs(logs.filter((log) => log.type === type));
  };

  const onNodeClick = (event, node) => {
    setTaskDetails(node);
  };

  // Обработчик соединения узлов
  const onConnect = (params) => {
    setEdges((eds) => addEdge(params, eds));
    setLogs((prevLogs) => [
      ...prevLogs,
      { type: 'info', message: `Connected ${params.source} -> ${params.target}` },
    ]);
  };

  return (
    <div style={{ backgroundColor: '#2a2f23', minHeight: '100vh', padding: '20px', color: '#c3e88d' }}>
      <h2 style={{ textAlign: 'center', color: '#9ccc65' }}>CI/CD Pipeline</h2>

      <div style={{ textAlign: 'center', marginBottom: '20px' }}>
        <button onClick={runPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#5cb85c', color: '#fff' }}>Run</button>
        <button onClick={stopPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#d9534f', color: '#fff' }}>Stop</button>
        <button onClick={restartPipeline} style={{ margin: '5px', padding: '10px', backgroundColor: '#5bc0de', color: '#fff' }}>Restart</button>
      </div>

      {/* Добавление новой задачи */}
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
          onConnect={onConnect}  // Обработчик соединений
          fitView
        >
          <MiniMap />
          <Controls />
          <Background color="#555" gap={16} />
        </ReactFlow>
      </div>

      {/* Детали задачи */}
      {taskDetails && (
        <div style={{ padding: '20px', margin: '20px auto', border: '1px solid #9ccc65', backgroundColor: '#394a34', width: '800px' }}>
          <h4>Task Details</h4>
          <p><strong>Name:</strong> {taskDetails.data.label}</p>
          <p><strong>Status:</strong> {taskDetails.status}</p>
          <p><strong>Start Time:</strong> {taskDetails.data.startTime || 'N/A'}</p>
          <p><strong>End Time:</strong> {taskDetails.data.endTime || 'N/A'}</p>
        </div>
      )}

      {/* Логи с фильтрацией */}
      <div style={{ padding: '20px', margin: '20px auto', border: '1px solid #9ccc65', backgroundColor: '#394a34', width: '800px' }}>
        <h4>Logs</h4>
        <div>
          {logTypes.map((type) => (
            <button key={type} onClick={() => filterLogs(type)} style={{ margin: '5px', padding: '5px', backgroundColor: '#9ccc65', color: '#2a2f23' }}>
              {type}
            </button>
          ))}
        </div>
        <div style={{ maxHeight: '150px', overflowY: 'auto' }}>
          {filteredLogs.map((log, index) => (
            <p key={index} style={{ margin: '5px 0' }}>
              [{log.type.toUpperCase()}] {log.message}
            </p>
          ))}
        </div>
      </div>
    </div>
  );
};

export default Pipeline;
