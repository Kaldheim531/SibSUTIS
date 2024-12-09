import React, { useState, useContext } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import api from '../api';
import { UserContext } from '../context/UserContext';

const Auth = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');
    const { setUser } = useContext(UserContext);
    const navigate = useNavigate();

    const handleLogin = async () => {
        try {
            const response = await api.post('token/', { username, password });
            localStorage.setItem('access_token', response.data.access);
            localStorage.setItem('refresh_token', response.data.refresh);

            // Получаем данные пользователя после входа
            const userResponse = await api.get('user/me/', {
                headers: { Authorization: `Bearer ${response.data.access}` },
            });
            setUser(userResponse.data); // Сохраняем пользователя в контексте

            navigate('/'); // Перенаправление на главную
        } catch (error) {
            setError('Вход не выполнен. Пожалуйста, проверьте правильность введения данных.');
        }
    };

    return (
        <div style={styles.container}>
            <div style={styles.formContainer}>
                <h2 style={styles.title}>Авторизация</h2>
                <p style={styles.label}>Имя пользователя</p>
                <InputWithFocus
                    type="text"
                    placeholder="Имя пользователя"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                />
                <p style={styles.label}>Пароль</p>
                <InputWithFocus
                    type="password"
                    placeholder="Пароль"
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                />
                <button onClick={handleLogin} style={styles.button}>Войти</button>
                {error && <p style={styles.error}>{error}</p>}

                <p style={styles.registerText}>
                    Нет аккаунта?{' '}
                    <Link to="/register" style={styles.registerLink}>Зарегистрироваться</Link>
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
        borderRadius: '40px',
        width: '450px', // Увеличиваем ширину
        boxShadow: '0px 6px 15px rgba(0, 0, 0, 0.1)', // Увеличенная тень для выделения формы
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
    },
    title: {
        textAlign: 'center',
        fontSize: '2.5rem', // Увеличиваем размер шрифта
        marginBottom: '2rem', // Увеличиваем отступ
        color: '#333',
        fontWeight: '600',
    },
    label: {
        width: '105%',
        fontSize: '1.3rem', // Увеличиваем размер шрифта
        color: '#000',
        marginBottom: '5px',
    },
    input: {
        width: '100%',
        padding: '16px', // Увеличиваем отступ
        margin: '12px 0', // Увеличиваем отступ
        border: '1px solid #ccc',
        borderRadius: '20px',
        fontSize: '1.1rem', // Увеличиваем размер шрифта
        outline: 'none',
        transition: '0.3s ease',
    },
    inputFocus: {
        borderColor: '#007bff',
        boxShadow: '0 0 8px rgba(0, 123, 255, 0.7)', // Увеличиваем тень при фокусе
    },
    button: {
        width: '100%',
        padding: '16px', // Увеличиваем отступ
        backgroundColor: '#1e0aa1',
        color: '#fff',
        fontSize: '1.3rem', // Увеличиваем размер шрифта
        border: 'none',
        borderRadius: '20px',
        cursor: 'pointer',
        marginTop: '20px', // Увеличиваем отступ
        transition: '0.3s ease',
    },
    error: {
        color: 'red',
        textAlign: 'center',
        fontSize: '0.9rem',
        marginTop: '10px',
    },
    registerText: {
        textAlign: 'center',
        fontSize: '1rem',
        marginTop: '20px',
        color: '#333',
    },
    registerLink: {
        color: '#1e0aa1',
        textDecoration: 'none',
        fontWeight: 'bold',
    },
};

// Добавим динамическое изменение стилей при фокусе на input
const InputWithFocus = ({ value, onChange, placeholder, type }) => {
    const [isFocused, setIsFocused] = useState(false);

    return (
        <input
            type={type}
            value={value}
            onChange={onChange}
            placeholder={placeholder}
            style={{
                ...styles.input,
                ...(isFocused ? styles.inputFocus : {}),
            }}
            onFocus={() => setIsFocused(true)}
            onBlur={() => setIsFocused(false)}
        />
    );
};

export default Auth;