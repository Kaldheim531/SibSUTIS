import React, { useState } from 'react';
import axios from 'axios';
import { useNavigate, Link } from 'react-router-dom';

const Register = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [message, setMessage] = useState('');
    const [error, setError] = useState('');
    const navigate = useNavigate();

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            await axios.post('http://localhost:8000/register/', {
                username,
                password,
            });
            setMessage('Registration successful. Redirecting to login...');
            setTimeout(() => navigate('/login'), 2000); // Перенаправление на страницу входа через 2 секунды
        } catch (error) {
            setError(error.response?.data?.detail || 'Registration failed.');
        }
    };

    return (
        <div style={styles.container}>
            <div style={styles.formContainer}>
                <h2 style={styles.title}>Register</h2>
                <form onSubmit={handleSubmit}>
                    <input
                        type="text"
                        value={username}
                        onChange={(e) => setUsername(e.target.value)}
                        placeholder="Username"
                        style={styles.input}
                        required
                    />
                    <input
                        type="password"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        placeholder="Password"
                        style={styles.input}
                        required
                    />
                    <button type="submit" style={styles.button}>Register</button>
                </form>
                {message && <p style={styles.success}>{message}</p>}
                {error && <p style={styles.error}>{error}</p>}

                <p style={styles.loginText}>
                    Already have an account?{' '}
                    <Link to="/login" style={styles.loginLink}>Login here</Link>
                </p>
            </div>
        </div>
    );
};

const styles = {
    container: {
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        height: '100vh',
        backgroundImage: 'url(/fon.png)', // Указываем путь к фону
        backgroundSize: 'cover',
        backgroundPosition: 'center',
        backgroundRepeat: 'no-repeat',
        padding: '20px',
        boxSizing: 'border-box',
    },
    formContainer: {
        backgroundColor: 'rgba(255, 255, 255, 0.9)', // Белый фон с прозрачностью для улучшения контраста
        padding: '40px',
        borderRadius: '10px',
        width: '350px',
        boxShadow: '0px 6px 15px rgba(0, 0, 0, 0.1)', // Мягкая тень для выделения
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
    },
    title: {
        textAlign: 'center',
        fontSize: '2.2rem',
        marginBottom: '1.5rem',
        color: '#333',
        fontWeight: '600',
    },
    input: {
        width: '100%',
        padding: '14px',
        margin: '10px 0',
        border: '1px solid #ccc',
        borderRadius: '8px',
        fontSize: '1rem',
        outline: 'none',
        transition: '0.3s ease',
    },
    inputFocus: {
        borderColor: '#007bff', // Изменение цвета при фокусе
        boxShadow: '0 0 5px rgba(0, 123, 255, 0.5)', // Легкая тень при фокусе
    },
    button: {
        width: '100%',
        padding: '14px',
        backgroundColor: '#007bff',
        color: '#fff',
        fontSize: '1.2rem',
        border: 'none',
        borderRadius: '8px',
        cursor: 'pointer',
        marginTop: '15px',
        transition: '0.3s ease',
    },
    buttonHover: {
        backgroundColor: '#0056b3', // Темный синий при наведении
    },
    success: {
        color: 'green',
        textAlign: 'center',
        fontSize: '0.9rem',
        marginTop: '10px',
    },
    error: {
        color: 'red',
        textAlign: 'center',
        fontSize: '0.9rem',
        marginTop: '10px',
    },
    loginText: {
        textAlign: 'center',
        fontSize: '1rem',
        marginTop: '20px',
        color: '#333',
    },
    loginLink: {
        color: '#007bff',
        textDecoration: 'none',
        fontWeight: 'bold',
    },
};

export default Register;
