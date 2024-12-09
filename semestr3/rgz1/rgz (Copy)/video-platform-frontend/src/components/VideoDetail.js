import React, { useEffect, useState } from 'react';
import api from '../api'; // Ваш конфиг для axios
import { useParams, useNavigate } from 'react-router-dom';
import axios from 'axios';

const VideoDetail = () => {
    const { id } = useParams();
    const [video, setVideo] = useState(null);
    const [comment, setComment] = useState('');
    const [comments, setComments] = useState([]);
    const navigate = useNavigate();

    useEffect(() => {
        const fetchVideoAndComments = async () => {
            try {
                const videoResponse = await api.get(`videos/${id}/`, {
                    headers: {
                        'Authorization': `Bearer ${localStorage.getItem('access_token')}`,
                    },
                });
                setVideo(videoResponse.data);

                const commentsResponse = await api.get(`videos/${id}/comments/`, {
                    headers: {
                        'Authorization': `Bearer ${localStorage.getItem('access_token')}`,
                    },
                });
                setComments(commentsResponse.data);
            } catch (error) {
                console.error('Error fetching video or comments:', error);
            }
        };
        fetchVideoAndComments();
    }, [id]);

    const handleCommentSubmit = async (e) => {
        e.preventDefault();

        if (!comment.trim()) return;

        try {
            const token = localStorage.getItem('access_token');
            const newComment = await submitComment(id, comment, token);
            setComments((prevComments) => [...prevComments, newComment]);
            setComment('');
        } catch (error) {
            console.error('Ошибка отправки сообщения:', error);
        }
    };

    const handleGoBack = () => {
        navigate(-1);
    };

    if (!video) {
        return <p>Loading...</p>;
    }

    return (
        <div style={styles.container}>
            <header style={styles.header}>

                <button onClick={handleGoBack} style={styles.backButton}>
                    Назад
                </button>
            </header>
            <main style={styles.main}>
                <div style={styles.videoAndChatContainer}>
                    <div style={styles.videoContainer}>
                        <video src={video.video_file} controls style={styles.videoPlayer} />
                    </div>
                    <div style={styles.chatContainer}>
                        <h3 style={styles.chatTitle}>Чат</h3>
                        <div style={styles.comments}>
                            {comments.length > 0 ? (
                                comments.map((comment) => (
                                    <div key={comment.id} style={styles.comment}>
                                        <p style={styles.commentUser}>{comment.user || 'Аноним'}:</p>
                                        <p style={styles.commentText}>{comment.text}</p>
                                    </div>
                                ))
                            ) : (
                                <p style={styles.noComments}>Нет комментариев</p>
                            )}
                        </div>
                        <form onSubmit={handleCommentSubmit} style={styles.commentForm}>
                            <textarea
                                value={comment}
                                onChange={(e) => setComment(e.target.value)}
                                placeholder="Напишите сообщение..."
                                style={styles.textarea}
                            />
                            <button type="submit" style={styles.sendButton}>
                                Отправить
                            </button>
                        </form>
                    </div>
                </div>
            </main>
        </div>
    );
};

const submitComment = async (videoId, text, token) => {
    try {
        const response = await axios.post(
            `http://localhost:8000/api/videos/${videoId}/comments/`,
            { text: text.trim(), video: videoId },
            {
                headers: {
                    'Authorization': `Bearer ${token}`,
                    'Content-Type': 'application/json',
                },
            }
        );
        return response.data;
    } catch (error) {
        console.error('Error posting comment:', error.response?.data || error.message);
        throw error;
    }
};

const styles = {
    container: {
        display: 'flex',
        flexDirection: 'column',
        minHeight: '100vh',
        color: '#999',
        fontFamily: 'Arial, sans-serif',
    },
    header: {
        display: 'flex',
        justifyContent: 'space-between',
        alignItems: 'center',
        padding: '10px 20px',
    },
    logo: {
        height: '40px',
    },
    backButton: {
        backgroundColor: '#210bb3',
        color: '#fff',
        border: 'none',
        padding: '15px 30px',
        borderRadius: '5px',
        cursor: 'pointer',
        marginLeft : '1500px',
    },
    main: {
        display: 'flex',
        flex: 1,
        padding: '20px',
    },
    videoAndChatContainer: {
        display: 'flex',
        flex: 1,
    },
    videoContainer: {
        flex: 2,
    },
    videoPlayer: {
        width: '100%',
        marginTop: '100px',
    },
    chatContainer: {
        flex: 1,
        backgroundColor: '#000000',
        padding: '20px',
        display: 'flex',
        flexDirection: 'column',
        height: '550px',
        marginTop: '100px',
    },
    chatTitle: {
        fontSize: '1.5rem',
        marginBottom: '20px',
        color: '#fff',
    },
    comments: {
        flex: 1,
        overflowY: 'auto',
        marginBottom: '20px',
        maxHeight: '400px',
    },
    comment: {
        backgroundColor: '#222',
        padding: '10px',
        marginBottom: '10px',
        borderRadius: '5px',
    },
    commentUser: {
        fontWeight: 'bold',
        marginBottom: '5px',
    },
    commentText: {
        fontSize: '0.9rem',
    },
    commentForm: {
        display: 'flex',
        flexDirection: 'column',
        gap: '10px',
    },
    textarea: {
        width: '100%',
        height: '80px',
        padding: '10px',
        borderRadius: '5px',
        border: '1px solid #555',
        color: '#fff',
        backgroundColor: '#fff',
        fontSize: '1rem',
        boxSizing: 'border-box', // Добавлено для корректного расчета ширины
    },
    sendButton: {
        width: '100%', // Изменено на 100% для растягивания по ширине
        padding: '10px 20px',
        backgroundColor: '#210bb3',
        color: '#fff',
        border: 'none',
        borderRadius: '5px',
        cursor: 'pointer',
    },
};

export default VideoDetail;