import React, { useEffect, useState } from 'react';
import api from '../api';
import { Link } from 'react-router-dom';

const VideoList = () => {
    const [videos, setVideos] = useState([]);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        const fetchVideos = async () => {
            try {
                const response = await api.get('videos/', {
                    headers: {
                        'Authorization': `Bearer ${localStorage.getItem('access_token')}`,
                    },
                });
                setVideos(response.data);
            } catch (error) {
                console.error(error);
            } finally {
                setLoading(false);
            }
        };
        fetchVideos();
    }, []);

    if (loading) {
        return <div>Loading videos...</div>;
    }

    return (
        <div style={styles.container}>
            <div style={styles.header}>
                <h1 style={styles.title}>Ваши видео</h1>
            </div>
            <div style={styles.videoList}>
                {videos.length > 0 ? (
                    videos.map((video) => (
                        <div key={video.id} style={styles.videoCard}>
                            <h2 style={styles.videoTitle}>{video.title}</h2>
                            <p style={styles.videoDescription}>{video.description}</p>
                            {/* Оборачиваем видео в Link для перехода */}
                            <Link to={`/video/${video.id}`} style={styles.link}>
                                <div style={styles.videoWrapper}>
                                    <video
                                        src={video.video_file}
                                        controls
                                        style={styles.videoPlayer}
                                    />
                                    {/* Добавляем полупрозрачный слой, чтобы сделать видео похожим на кнопку */}
                                    <div style={styles.overlay}>
                                        <span style={styles.overlayText}>Воспроизвести</span>
                                    </div>
                                </div>
                            </Link>
                        </div>
                    ))
                ) : (
                    <p style={styles.noVideos}>Нет ни одного загруженного видео.</p>
                )}
            </div>

            {/* Кнопка для возврата на главную страницу */}
            <Link to="/" style={styles.backButton}>
                Главная
            </Link>
        </div>
    );
};

const styles = {
    container: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'flex-start',
        height: '100vh',
        backgroundImage: 'url(/fon.png)', // Фон для страницы
        backgroundSize: 'cover',
        backgroundPosition: 'center',
        padding: '20px',
        color: '#fff',
    },
    header: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        marginBottom: '30px',
    },
    title: {
        fontSize: '2.5rem',
        marginBottom: '10px',
        color: '#fff',
    },
    videoList: {
        display: 'grid',
        gridTemplateColumns: 'repeat(auto-fill, minmax(300px, 1fr))',
        gap: '20px',
        maxWidth: '1200px',
        width: '100%',
        margin: '0 auto',
    },
    videoCard: {
        backgroundColor: 'rgba(0, 0, 0, 0.3)', // Прозрачный фон для карточки
        padding: '15px',
        borderRadius: '20px',
        boxShadow: '0 4px 8px rgba(0, 0, 0, 0.2)',
        color: '#fff',
    },
    videoTitle: {
        fontSize: '2rem',
        marginBottom: '20px',
        fontWeight: 'bold',
    },
    videoDescription: {
        fontSize: '1.2rem',
        marginBottom: '30px',
        color: '#ccc',
    },
    videoWrapper: {
        position: 'relative', // Для размещения наложения поверх видео
    },
    videoPlayer: {
        width: '100%',
        borderRadius: '20px',
    },
    overlay: {
        position: 'absolute',
        top: 0,
        left: 0,
        width: '100%',
        height: '100%',
        backgroundColor: 'rgba(0, 0, 0, 0)', // Темный полупрозрачный слой
        color: '#fff',
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        borderRadius: '8px',
        opacity: 0,
        transition: 'opacity 0.3s ease', // Плавный переход при наведении
    },
    overlayText: {
        fontSize: '1.5rem',
        fontWeight: 'bold',
    },
    link: {
        display: 'block',
        textDecoration: 'none', // Убираем подчеркивание
    },
    noVideos: {
        fontSize: '1.2rem',
        color: '#fff',
        textAlign: 'center',
    },
    backButton: {
        marginTop: '20px',
        padding: '20px 40px',
        backgroundColor: '#210bb3',
        color: '#fff',
        textDecoration: 'none',
        borderRadius: '20px',
        cursor: 'pointer',
        fontSize: '1.7rem',
    },
};

export default VideoList;
