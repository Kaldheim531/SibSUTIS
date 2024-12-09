import React, { useContext } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { UserContext } from '../context/UserContext';

const Home = () => {
    const { user, setUser } = useContext(UserContext);
    const navigate = useNavigate();

    // Функция выхода
    const handleLogout = () => {
        // Удаляем токены из localStorage
        localStorage.removeItem('access_token');
        localStorage.removeItem('refresh_token');

        // Очищаем данные пользователя в контексте
        setUser(null);

        // Перенаправляем на страницу входа
        navigate('/login');
    };

    return (
        <div style={styles.container}>
            {/* Верхний правый угол: имя пользователя и кнопка Logout */}
            {user && (
                <div style={styles.userInfo}>
                    <p style={styles.username}>Logged in as: <strong>{user.username}</strong></p>
                    <button style={styles.button} onClick={handleLogout}>Logout</button>
                </div>
            )}
            
            <h1 style={styles.title}>Welcome to Video Platform</h1>

            {user ? (
                <div style={styles.buttonContainer}>
                    <Link to="/videos">
                        <button style={styles.button}>View Videos</button>
                    </Link>
                    <Link to="/upload">
                        <button style={styles.button}>Upload Video</button>
                    </Link>
                </div>
            ) : (
                <>
                    <div style={styles.buttonContainer}>
                        <Link to="/login">
                            <button style={styles.button}>Login</button>
                        </Link>
                    </div>
                    <div style={styles.buttonContainer}>
                        <Link to="/register">
                            <button style={styles.button}>Register</button>
                        </Link>
                    </div>
                </>
            )}
        </div>
    );
};

const styles = {
    container: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'center',
        height: '100vh',
        backgroundImage: 'url(/fon.png)', // фон
        backgroundSize: 'cover',
        backgroundPosition: 'center',
        backgroundRepeat: 'no-repeat',
        color: '#fff', // Текст белым цветом
        textAlign: 'center', // Центрирование текста
        padding: '20px',
        boxSizing: 'border-box',
        position: 'relative', // Это необходимо для позиционирования элементов в верхнем правом углу
    },
    title: {
        fontSize: '2.5rem',
        marginBottom: '2rem',
        fontWeight: '700', // Увеличим вес шрифта для заголовка
        textShadow: '2px 2px 8px rgba(0, 0, 0, 0.7)', // Тень для текста заголовка
    },
    buttonContainer: {
        margin: '1rem',
    },
    button: {
        padding: '1rem 2rem',
        fontSize: '1.1rem',
        cursor: 'pointer',
        backgroundColor: '#007bff',
        color: '#fff',
        border: 'none',
        borderRadius: '8px', // Закругление углов
        boxShadow: '0px 4px 8px rgba(0, 0, 0, 0.2)', // Тень для кнопок
        transition: 'all 0.3s ease-in-out', // Плавное изменение для анимации
    },
    buttonHover: {
        transform: 'translateY(-3px)', // Подъем кнопки при наведении
        boxShadow: '0px 6px 12px rgba(0, 0, 0, 0.3)', // Увеличенная тень
    },
    userInfo: {
        position: 'absolute', // Фиксируем в верхнем правом углу
        top: '20px',
        right: '1px', // Позиционируем элемент в правом верхнем углу
        fontSize: '1.2rem',
        textAlign: 'right',
        backgroundColor: 'rgba(0, 0, 0, 0.5)', // Полупрозрачный фон для контраста
        padding: '10px',
        borderRadius: '8px',
        boxShadow: '0px 4px 8px rgba(0, 0, 0, 0.2)', // Тень для контейнера с именем и кнопкой
    },
    username: {
        fontSize: '1.1rem',
        fontWeight: '500',
        marginBottom: '0.5rem',
    },
};

// Для применения анимации при наведении, нужно использовать событие onMouseEnter и onMouseLeave
const ButtonWithHoverEffect = ({ onClick, children, style }) => {
    const [isHovered, setIsHovered] = React.useState(false);

    return (
        <button
            onClick={onClick}
            style={{ ...style, ...(isHovered ? styles.buttonHover : {}) }}
            onMouseEnter={() => setIsHovered(true)}
            onMouseLeave={() => setIsHovered(false)}
        >
            {children}
        </button>
    );
};

export default Home;
