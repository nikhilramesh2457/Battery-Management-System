FROM python:3.9

ENV TZ="Asia/Kolkata"
RUN date

# Set timezone:
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && echo $CONTAINER_TIMEZONE > /etc/timezone

VOLUME [srv/app]

WORKDIR /srv

COPY ./requirements.txt /srv/requirements.txt
RUN pip install --no-cache-dir --upgrade -r /srv/requirements.txt

EXPOSE 8080

CMD ["fastapi", "run", "app/main.py", "--port", "8080"]