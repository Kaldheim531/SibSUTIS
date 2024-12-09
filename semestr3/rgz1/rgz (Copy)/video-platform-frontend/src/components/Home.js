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
            {/* Если пользователь вошел, показываем информацию */}
            {user && (
                <div style={styles.userInfoContainer}>
                    <p style={styles.username}>Вы вошли как: <strong>{user.username}</strong></p>
                    <button style={styles.button} onClick={handleLogout}>Выйти</button>
                </div>
            )}
            
            <h1 style={styles.title}>Добро пожаловать!</h1>
            <h1 style={styles.title}>YADROTube</h1>

            {user ? (
                <div style={styles.buttonContainer}>
                    <Link to="/videos">
                        <button style={styles.button}>Просмотреть видео</button>
                    </Link>
                    <Link to="/upload">
                        <button style={styles.button}>Загрузить видео</button>
                    </Link>
                </div>
            ) : (
                <>
                    <div style={styles.buttonContainer}>
                        <Link to="/login">
                            <button style={styles.button}>Войти</button>
                        </Link>
                    </div>
                    <div style={styles.buttonContainer}>
                        <Link to="/register">
                            <button style={styles.button}>Зарегистрироваться</button>
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
        height: '60vh',
        backgroundImage: 'url(/fon.png)', // фон
        backgroundSize: 'cover',
        backgroundPosition: 'center',
        backgroundRepeat: 'no-repeat',
        color: '#fff', // Текст белым цветом
        textAlign: 'center', // Центрирование текста
        padding: '20px',
        boxSizing: 'border-box',
        position: 'relative', // Это необходимо для позиционирования элементов
    },
    title: {
        fontSize: '2.3rem',
        marginBottom: '1rem',
        fontWeight: '700', // Увеличим вес шрифта для заголовка
        textShadow: '2px 2px 2px rgba(0, 0, 0, 0.7)', // Тень для текста заголовка
    },
    buttonContainer: {
        margin: '1rem',
    },
    button: {
        padding: '1rem 3rem',
        fontSize: '1rem',
        cursor: 'pointer',
        backgroundColor: '#1e0aa1',
        color: '#fff',
        border: 'none',
        borderRadius: '20px', // Закругление углов
        boxShadow: '0px 4px 8px rgba(0, 0, 0, 0.2)', // Тень для кнопок
        transition: 'all 0.3s ease-in-out', // Плавное изменение для анимации
    },
    userInfoContainer: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        gap: '1rem', // Расстояние между элементами
        marginBottom: '2rem', // Отступ снизу для разделения с остальными элементами
    },
    username: {
        fontSize: '1.5rem',
        fontWeight: '500',
        textAlign: 'center',
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
