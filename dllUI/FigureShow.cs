using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace dllUI
{
    public partial class FigureShow : Form
    {

        private static int scale = 5;
        private Point pointOfPainting;
        bool _moving = false;
        private int deltaX = 0;
        private int deltaY = 0;
        List<SolidBrush> brushes = new List<SolidBrush>();
        List<bool> fillFigure = new List<bool>();
        public FigureShow()
        {
            Random r = new Random();
            foreach (var shape in Form1.shapes)
            {
                SolidBrush brush = new SolidBrush(Color.FromArgb(255, (byte)r.Next(256), (byte)r.Next(256), (byte)r.Next(256)));
                brushes.Add(brush);
            }
            pointOfPainting = new Point(this.Width / 5, this.Height / 5);
            InitializeComponent();
        }

        private List<List<Point>> convertNums(List<List<double>> coordinates)
        {
            List < List < Point >> Figures = new List<List <Point>> ();
            foreach (List<double> shape in coordinates)
            {
                List < Point > points = new List<Point> ();
                if(shape.Count == 2) 
                {
                    double margin = 2.0;
                    points.Add(new Point((int) (pointOfPainting.X + shape[0]*scale - (margin * (scale - 4))), 
                        (int) (pointOfPainting.Y + shape[1]*scale - (margin * (scale - 4)))));
                    points.Add(new Point((int)(pointOfPainting.X + shape[0]*scale + (margin * (scale - 4))), 
                        (int)(pointOfPainting.Y + shape[1] * scale - (margin*(scale-4)))));
                    points.Add(new Point((int)(pointOfPainting.X + shape[0] * scale + (margin * (scale - 4))), 
                        (int)(pointOfPainting.Y + shape[1] * scale + (margin * (scale - 4)))));
                    points.Add(new Point((int)(pointOfPainting.X + shape[0] * scale - (margin * (scale - 4))), 
                        (int)(pointOfPainting.Y + shape[1] * scale + (margin * (scale - 4)))));
                    points.Add(new Point((int)(pointOfPainting.X + shape[0] * scale - (margin * (scale - 4))),
                        (int)(pointOfPainting.Y + shape[1] * scale - (margin * (scale - 4)))));
                    fillFigure.Add(true);
                }
                else
                {
                    for (int i = 1; i < shape.Count; i += 2)
                    {
                        points.Add(new Point((int)(pointOfPainting.X + shape[i - 1] * scale), (int)(pointOfPainting.Y + shape[i] * scale)));
                    }
                    if ((shape[0] < shape[shape.Count - 2] +0.01 && shape[0] > shape[shape.Count - 2] - 0.01)
                        && (shape[1] < shape[shape.Count - 1] + 0.01 && shape[1] > shape[shape.Count - 1] - 0.01)) 
                        fillFigure.Add(true);
                    else fillFigure.Add(false);
                }
                Figures.Add (points);
            }
            return Figures;    
        }
        private void FigureShow_Paint(object sender, PaintEventArgs e)
        {
            List<List<Point>> shapes = convertNums(Form1.shapes);
            Graphics g = this.CreateGraphics();
            using(Pen pn = new Pen(Brushes.Black))
            {
                
                for(int i = 0; i < shapes.Count; i++)
                {
                    if (fillFigure[i])
                    {
                        GraphicsPath gp = new GraphicsPath();
                        gp.AddLines(shapes[i].ToArray());
                        gp.CloseFigure();
                        g.FillPath(brushes[i], gp);
                    }
                    g.DrawLines(pn, shapes[i].ToArray());
                }
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            scale = trackBar1.Value;
            this.Invalidate();
        }


        private void FigureShow_MouseUp(object sender, MouseEventArgs e)
        {
            _moving = false;
        }

        private void FigureShow_MouseDown(object sender, MouseEventArgs e)
        {
            _moving = true;
            deltaX = e.X - pointOfPainting.X;
            deltaY = e.Y - pointOfPainting.Y;
        }

        private void FigureShow_MouseMove(object sender, MouseEventArgs e)
        {
            if(_moving)
            {
                pointOfPainting.X = e.X - deltaX;
                pointOfPainting.Y = e.Y - deltaY;
                this.Invalidate();
            }
        }

        private void FigureShow_Load(object sender, EventArgs e)
        {
            System.Windows.Forms.ToolTip t = new System.Windows.Forms.ToolTip();
            t.SetToolTip(trackBar1, "Выберите нужный масштаб");
        }
    }
}